#include "Parser.hpp"
using std::any_cast;
using std::static_pointer_cast;
Parser::Parser(string path, vector<Token>& tokens)
	: path{path}
	, tokens{tokens}
	, tokenPointer{0}
{
}
Module Parser::Program()
{
	int32_t line = Look().line;
	int32_t column = Look().column;
	vector<ExpPtr> expressions;
	while (!IsEof())
	{
		expressions.push_back(Statement());
	}
	ExpPtr tree = Ast::Block(line, column, expressions);
	return Module(path, tree);
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
ExpPtr Parser::DefineVariable()
{
	int32_t line = Look().line;
	int32_t column = Look().column;
	Match(Tag::DefVar);
	Token& token = Look();
	Match(Tag::Identifier);
	wstring name = any_cast<wstring>(token.value);
	Match(Tag::Colon);
	Type t = ParseType();
	Match(Tag::Assign);
	ExpPtr value = And();
	return Ast::DefineVariable(line, column, name, t, value);
}
ExpPtr Parser::DefineFunction()
{
	int32_t line = Look().line;
	int32_t column = Look().column;
	Match(Tag::DefFun);
	Token& token = Look();
	Match(Tag::Identifier);
	wstring name = any_cast<wstring>(token.value);
	Match(Tag::LeftParenthesis);
	if (Look().tag == Tag::RightParenthesis)
	{
		Move();
		Match(Tag::Colon);
		Type returnType = ParseType();
		ExpPtr body = Block();
		return Ast::DefineFunction(line, column, name,
								   vector<ParameterExpPtr>(), body, returnType);
	}
	else
	{
		token = Look();
		Match(Tag::Identifier);
		wstring parameterName = any_cast<wstring>(token.value);
		Match(Tag::Colon);
		Type t = ParseType();
		vector<ParameterExpPtr> parameters;
		parameters.push_back(
			Ast::Parameter(token.line, token.column, parameterName, t));
		while (Look().tag != Tag::RightParenthesis)
		{
			Match(Tag::Comma);
			token = Look();
			Match(Tag::Identifier);
			parameterName = any_cast<wstring>(token.value);
			Match(Tag::Colon);
			t = ParseType();
			parameters.push_back(
				Ast::Parameter(token.line, token.column, parameterName, t));
		}
		Move();
		Match(Tag::Colon);
		Type returnType = ParseType();
		ExpPtr body = Block();
		return Ast::DefineFunction(line, column, name, parameters, body,
								   returnType);
	}
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
	case Tag::DefVar:
		return DefineVariable();
	case Tag::DefFun:
		return DefineFunction();
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
		int line = Look().line;
		int column = Look().column;
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
		int line = Look().line;
		int column = Look().column;
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
		int line = Look().line;
		int column = Look().column;
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
		int line = Look().line;
		int column = Look().column;
		Move();
		return Ast::GreaterThan(line, column, x, Expr());
	}
	case Tag::LessThan:
	{
		int line = Look().line;
		int column = Look().column;
		Move();
		return Ast::LessThan(line, column, x, Expr());
	}
	case Tag::GreaterThanOrEqual:
	{
		int line = Look().line;
		int column = Look().column;
		Move();
		return Ast::GreaterThanOrEqual(line, column, x, Expr());
	}
	case Tag::LessThanOrEqual:
	{
		int line = Look().line;
		int column = Look().column;
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
		int line = Look().line;
		int column = Look().column;
		Move();
		return Ast::UnaryPlus(line, column, Unary());
	}
	else if (Look().tag == Tag::Subtract)
	{
		int line = Look().line;
		int column = Look().column;
		Move();
		return Ast::UnaryMinus(line, column, Unary());
	}
	else if (Look().tag == Tag::Not)
	{
		int line = Look().line;
		int column = Look().column;
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
	while (Look().tag == Tag::LeftParenthesis)
	{
		Token& token = Look();
		Move();
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
		throw SyntaxException(token.line, token.column, L"syntax error");
	}
}
Type Parser::ParseType()
{
	Token& token = Look();
	Match(Tag::Identifier);
	wstring name = any_cast<wstring>(token.value);
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
		return Type(name, types);
	}
	else
	{
		return Type(name, vector<Type>());
	}
}