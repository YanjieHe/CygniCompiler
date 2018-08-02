#include "Parser.hpp"
using std::any_cast;
using std::static_pointer_cast;
Parser::Parser(string path, vector<Token>& tokens)
	: path{path}
	, tokens{tokens}
	, tokenPointer{0}
{
}
CodeFile Parser::Program()
{
	Match(Tag::Namespace);
	vector<wstring> ns = ParseNamespace();

	unordered_map<wstring, Module> modules;
	unordered_map<wstring, Class> classes;
	unordered_map<wstring, shared_ptr<Namespace>> uses;
	while (!IsEof())
	{
		AccessModifier am = ParseAM(Look());
		Move();
		if (Look().tag == Tag::Class)
		{
			Class classInfo = DefClass(am);
			classes.insert({classInfo.type.name, classInfo});
		}
		else if (Look().tag == Tag::Module)
		{
			Module moduleInfo = DefModule(am);
			modules.insert({moduleInfo.type.name, moduleInfo});
		}
		else
		{
			throw SyntaxException(Look().line, Look().column,
								  L"expecting 'class' or 'module'");
		}
	}
	return CodeFile(path, ns, modules, classes, uses);
}
ExpPtr Parser::Block()
{
	int32_t line = Look().line;
	int32_t column = Look().column;
	vector<ExpPtr> expressions;
	Match(Tag::LeftBrace);
	while (Look().tag != Tag::RightBrace)
	{
		expressions.push_back(Statement());
	}
	Move();
	return Ast::Block(line, column, expressions);
}
ExpPtr Parser::If()
{
	int32_t line = Look().line;
	int32_t column = Look().column;
	Match(Tag::If);
	ExpPtr condition = And();
	ExpPtr ifTrue = Block();
	if (Look().tag == Tag::Else)
	{
		Move();
		if (Look().tag == Tag::If)
		{
			ExpPtr ifFalse = If();
			return Ast::IfThenElse(line, column, condition, ifTrue, ifFalse);
		}
		else
		{
			ExpPtr ifFalse = Block();
			return Ast::IfThenElse(line, column, condition, ifTrue, ifFalse);
		}
	}
	else
	{
		return Ast::IfThen(line, column, condition, ifTrue);
	}
}
ExpPtr Parser::While()
{
	int32_t line = Look().line;
	int32_t column = Look().column;
	Match(Tag::While);
	ExpPtr condition = And();
	ExpPtr body = Block();
	return Ast::While(line, column, condition, body);
}
AccessModifier Parser::ParseAM(Token& token)
{
	if (token.tag == Tag::Public)
	{
		return AccessModifier::Public;
	}
	else if (token.tag == Tag::Private)
	{
		return AccessModifier::Private;
	}
	else if (token.tag == Tag::Protected)
	{
		return AccessModifier::Protected;
	}
	else if (token.tag == Tag::Internal)
	{
		return AccessModifier::Internal;
	}
	else
	{
		throw SyntaxException(token.line, token.column,
							  L"expecting access modifier");
	}
}
Module Parser::DefModule(AccessModifier modifier)
{
	Match(Tag::Module);
	Type moduleType = ParseType();
	moduleType.kind = TypeKind::Module;
	Match(Tag::LeftBrace);
	vector<Field> fields;
	vector<Function> functions;
	vector<NativeFunction> nativeFunctions;
	while (Look().tag != Tag::RightBrace)
	{
		if (Look().tag == Tag::Native)
		{
			nativeFunctions.push_back(DefNativeFunction());
		}
		else
		{
			AccessModifier am = ParseAM(Look());
			Move();
			if (Look().tag == Tag::DefVar)
			{
				Field field = DefField(am);
				fields.push_back(field);
			}
			else if (Look().tag == Tag::DefFun)
			{
				Function function = DefFunction(am);
				functions.push_back(function);
			}
			else
			{
				throw SyntaxException(Look().line, Look().column,
									  L"expecting 'var' or 'fun'");
			}
		}
	}
	Match(Tag::RightBrace);
	// TO DO: initializer
	return Module(modifier, moduleType, fields, functions, nativeFunctions);
}
Class Parser::DefClass(AccessModifier modifier)
{
	Match(Tag::Class);
	Type classType = ParseType();
	classType.kind = TypeKind::Class;
	Match(Tag::LeftBrace);
	vector<Field> fields;
	vector<Function> methods;
	unordered_map<wstring, Function> constructors;
	while (Look().tag != Tag::RightBrace)
	{
		AccessModifier am = ParseAM(Look());
		Move();
		if (Look().tag == Tag::DefVar)
		{
			Field field = DefField(am);
			fields.push_back(field);
		}
		else if (Look().tag == Tag::DefFun)
		{
			Function method = DefFunction(am);
			methods.push_back(method);
		}
		else
		{
			throw SyntaxException(Look().line, Look().column,
								  L"expecting 'var' or 'fun'");
		}
	}
	Match(Tag::RightBrace);
	return Class(modifier, classType, fields, methods, constructors);
}
Function Parser::DefFunction(AccessModifier modifier)
{
	Match(Tag::DefFun);
	wstring name = ParseIdentifier();
	Match(Tag::LeftParenthesis);
	vector<Parameter> parameters;
	if (Look().tag == Tag::RightParenthesis)
	{
		Match(Tag::RightParenthesis);
	}
	else
	{
		parameters.push_back(ParseParameter());
		while (Look().tag != Tag::RightParenthesis)
		{
			Match(Tag::Comma);
			parameters.push_back(ParseParameter());
		}
		Match(Tag::RightParenthesis);
	}
	Match(Tag::Colon);
	Type returnType = ParseType();
	Match(Tag::LeftBrace);
	vector<LocalVariable> variables;
	while (Look().tag == Tag::DefVar)
	{
		variables.push_back(DefLocalVariable());
	}
	vector<ExpPtr> expressions;
	while (Look().tag != Tag::RightBrace)
	{
		expressions.push_back(Statement());
	}
	Match(Tag::RightBrace);
	return Function(modifier, name, parameters, variables, expressions,
					returnType);
}
Parameter Parser::ParseParameter()
{
	wstring name = ParseIdentifier();
	Match(Tag::Colon);
	Type type = ParseType();
	return Parameter(name, type);
}
LocalVariable Parser::DefLocalVariable()
{
	Match(Tag::DefVar);
	wstring name = ParseIdentifier();
	Match(Tag::Colon);
	Type type = ParseType();
	Match(Tag::Assign);
	ExpPtr value = Or();
	return LocalVariable(name, type, value);
}
Field Parser::DefField(AccessModifier modifier)
{
	Match(Tag::DefVar);
	wstring name = ParseIdentifier();
	Match(Tag::Colon);
	Type type = ParseType();
	Match(Tag::Assign);
	ExpPtr value = Or();
	return Field(modifier, name, type, value);
}
NativeFunction Parser::DefNativeFunction()
{
	Match(Tag::Native);
	Match(Tag::LeftParenthesis);
	wstring libraryName = ParseStringLiteral();
	Match(Tag::Comma);
	wstring functionName = ParseStringLiteral();
	Match(Tag::RightParenthesis);
	AccessModifier modifier = ParseAM(Look());
	Move();
	Match(Tag::DefFun);
	wstring name = ParseIdentifier();
	Match(Tag::LeftParenthesis);
	vector<Parameter> parameters;
	if (Look().tag == Tag::RightParenthesis)
	{
		Match(Tag::RightParenthesis);
	}
	else
	{
		parameters.push_back(ParseParameter());
		while (Look().tag != Tag::RightParenthesis)
		{
			Match(Tag::Comma);
			parameters.push_back(ParseParameter());
		}
		Match(Tag::RightParenthesis);
	}
	Match(Tag::Colon);
	Type returnType = ParseType();
	Match(Tag::LeftBrace);
	vector<LocalVariable> variables;
	while (Look().tag == Tag::DefVar)
	{
		variables.push_back(DefLocalVariable());
	}
	vector<ExpPtr> expressions;
	while (Look().tag != Tag::RightBrace)
	{
		expressions.push_back(Statement());
	}
	Match(Tag::RightBrace);
	return NativeFunction(libraryName, functionName, L"", modifier, name,
						  parameters, returnType);
}
ExpPtr Parser::Return()
{
	Token& token = Look();
	Match(Tag::Return);
	ExpPtr value = And();
	return Ast::Return(token.line, token.column, value);
}
ExpPtr Parser::Statement()
{
	switch (Look().tag)
	{
	case Tag::If:
		return If();
	case Tag::Return:
		return Return();
	case Tag::While:
		return While();
	default:
		return Assign();
	}
}
ExpPtr Parser::Assign()
{
	ExpPtr x = And();
	if (x->kind == ExpressionKind::Variable && Look().tag == Tag::Assign)
	{
		int32_t line = Look().line;
		int32_t column = Look().column;
		Move();
		VariableExpPtr variable = static_pointer_cast<VariableExpression>(x);
		return Ast::Assign(line, column, variable->name, And());
	}
	else
	{
		return x;
	}
}
ExpPtr Parser::Or()
{
	ExpPtr x = And();
	while (Look().tag == Tag::Or)
	{
		int32_t line = Look().line;
		int32_t column = Look().column;
		Move();
		x = Ast::Or(line, column, x, And());
	}
	return x;
}
ExpPtr Parser::And()
{
	ExpPtr x = Equality();
	while (Look().tag == Tag::And)
	{
		int32_t line = Look().line;
		int32_t column = Look().column;
		Move();
		x = Ast::And(line, column, x, Equality());
	}
	return x;
}
ExpPtr Parser::Equality()
{
	ExpPtr x = Relation();
	while (Look().tag == Tag::Equal || Look().tag == Tag::NotEqual)
	{
		Token& token = Look();
		Move();
		if (token.tag == Tag::Equal)
		{
			x = Ast::Equal(token.line, token.column, x, Relation());
		}
		else
		{
			x = Ast::NotEqual(token.line, token.column, x, Relation());
		}
	}
	return x;
}
ExpPtr Parser::Relation()
{
	ExpPtr x = Expr();
	switch (Look().tag)
	{
	case Tag::GreaterThan:
	{
		int32_t line = Look().line;
		int32_t column = Look().column;
		Move();
		return Ast::GreaterThan(line, column, x, Expr());
	}
	case Tag::LessThan:
	{
		int32_t line = Look().line;
		int32_t column = Look().column;
		Move();
		return Ast::LessThan(line, column, x, Expr());
	}
	case Tag::GreaterThanOrEqual:
	{
		int32_t line = Look().line;
		int32_t column = Look().column;
		Move();
		return Ast::GreaterThanOrEqual(line, column, x, Expr());
	}
	case Tag::LessThanOrEqual:
	{
		int32_t line = Look().line;
		int32_t column = Look().column;
		Move();
		return Ast::LessThanOrEqual(line, column, x, Expr());
	}
	default:
		return x;
	}
}
ExpPtr Parser::Expr()
{
	ExpPtr x = Term();
	while (Look().tag == Tag::Add || Look().tag == Tag::Subtract)
	{
		Token& token = Look();
		Move();
		if (token.tag == Tag::Add)
		{
			x = Ast::Add(token.line, token.column, x, Term());
		}
		else
		{
			x = Ast::Subtract(token.line, token.column, x, Term());
		}
	}
	return x;
}
ExpPtr Parser::Term()
{
	ExpPtr x = Unary();
	while (Look().tag == Tag::Multiply || Look().tag == Tag::Divide ||
		   Look().tag == Tag::Modulo)
	{
		Token& token = Look();
		Move();
		if (token.tag == Tag::Multiply)
		{
			x = Ast::Multiply(token.line, token.column, x, Unary());
		}
		else if (token.tag == Tag::Divide)
		{
			x = Ast::Divide(token.line, token.column, x, Unary());
		}
		else
		{
			x = Ast::Modulo(token.line, token.column, x, Unary());
		}
	}
	return x;
}
ExpPtr Parser::Unary()
{
	if (Look().tag == Tag::Add)
	{
		int32_t line = Look().line;
		int32_t column = Look().column;
		Move();
		return Ast::UnaryPlus(line, column, Unary());
	}
	else if (Look().tag == Tag::Subtract)
	{
		int32_t line = Look().line;
		int32_t column = Look().column;
		Move();
		return Ast::UnaryMinus(line, column, Unary());
	}
	else if (Look().tag == Tag::Not)
	{
		int32_t line = Look().line;
		int32_t column = Look().column;
		Move();
		return Ast::Not(line, column, Unary());
	}
	else
	{
		return Postfix();
	}
}
ExpPtr Parser::Postfix()
{
	ExpPtr x = Factor();
	while (Look().tag == Tag::LeftParenthesis || Look().tag == Tag::Dot ||
		   Look().tag == Tag::LeftBracket)
	{
		Token& token = Look();
		Move();
		if (token.tag == Tag::LeftParenthesis)
		{
			vector<ExpPtr> arguments;
			if (Look().tag == Tag::RightParenthesis)
			{
				x = Ast::Call(token.line, token.column, x, arguments);
			}
			else
			{
				arguments.push_back(And());
			}
			while (Look().tag != Tag::RightParenthesis)
			{
				Match(Tag::Comma);
				arguments.push_back(And());
			}
			Move();
			x = Ast::Call(token.line, token.column, x, arguments);
		}
		else if (token.tag == Tag::Dot)
		{
			wstring name = ParseIdentifier();
			x = Ast::Dot(token.line, token.column, x, name);
		}
		else
		{
			throw wstring(L"not implemented");
		}
	}
	return x;
}
ExpPtr Parser::Factor()
{
	Token& token = Look();
	switch (token.tag)
	{
	case Tag::Int:
	case Tag::Long:
	case Tag::Float:
	case Tag::Double:
	case Tag::Char:
	case Tag::String:
	{
		Move();
		return Ast::Constant(token.line, token.column, token.value);
	}
	case Tag::True:
	{
		Move();
		return Ast::Constant(token.line, token.column, true);
	}
	case Tag::False:
	{
		Move();
		return Ast::Constant(token.line, token.column, false);
	}
	case Tag::LeftParenthesis:
	{
		Move();
		ExpPtr exp = And();
		Match(Tag::RightParenthesis);
		return exp;
	}
	case Tag::Identifier:
	{
		Move();
		wstring name = any_cast<wstring>(token.value);
		return Ast::Variable(token.line, token.column, name);
	}
	default:
		throw SyntaxException(token.line, token.column,
							  L"syntax error: " + TokenTagToString(token.tag));
	}
}
Type Parser::ParseType()
{
	wstring name = ParseIdentifier();
	if (Look().tag == Tag::LeftBracket)
	{
		Move();
		vector<Type> types;
		types.push_back(ParseType());
		while (Look().tag != Tag::RightBracket)
		{
			Match(Tag::Comma);
			Type t = ParseType();
			types.push_back(t);
		}
		Move();
		return Type(ParseTypeKind(name), name, types);
	}
	else
	{
		return Type(ParseTypeKind(name), name, vector<Type>());
	}
}
TypeKind Parser::ParseTypeKind(wstring text)
{
	static unordered_map<wstring, TypeKind> kinds = {
		{L"Int", TypeKind::Int},		 {L"Long", TypeKind::Long},
		{L"Float", TypeKind::Float},	 {L"Double", TypeKind::Double},
		{L"Boolean", TypeKind::Boolean}, {L"Char", TypeKind::Char},
		{L"String", TypeKind::String},   {L"Unit", TypeKind::Unit},
		{L"Array", TypeKind::Array},	 {L"Function", TypeKind::Function}};
	if (kinds.find(text) != kinds.end())
	{
		return kinds[text];
	}
	else
	{
		return TypeKind::Object;
	}
}
vector<wstring> Parser::ParseNamespace()
{
	vector<wstring> ns;
	ns.push_back(ParseIdentifier());
	while (Look().tag == Tag::Dot)
	{
		Match(Tag::Dot);
		ns.push_back(ParseIdentifier());
	}
	return ns;
}