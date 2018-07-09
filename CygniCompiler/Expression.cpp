#include "Expression.hpp"
using std::make_shared;
Expression::Expression(int32_t line, int32_t column, ExpressionKind kind)
	: line{line}
	, column(column)
	, kind{kind}
{
	static int currentID = 0;
	this->ID = currentID;
	currentID++;
}
ConstantExpression::ConstantExpression(int32_t line, int32_t column, any value)
	: Expression(line, column, ExpressionKind::Constant)
	, value{value}
{
}

UnaryExpression::UnaryExpression(int32_t line, int32_t column,
								 ExpressionKind kind, ExpPtr operand)
	: Expression(line, column, kind)
	, operand{operand}
{
}

BinaryExpression::BinaryExpression(int32_t line, int32_t column,
								   ExpressionKind kind, ExpPtr left,
								   ExpPtr right)
	: Expression(line, column, kind)
	, left{left}
	, right{right}
{
}

AssignExpression::AssignExpression(int32_t line, int32_t column, wstring name,
								   ExpPtr value)
	: Expression(line, column, ExpressionKind::Assign)
	, name{name}
	, value{value}
{
}

BlockExpression::BlockExpression(int32_t line, int32_t column,
								 vector<ExpPtr> expressions)
	: Expression(line, column, ExpressionKind::Block)
	, expressions{expressions}
{
}

IfThenExpression::IfThenExpression(int32_t line, int32_t column,
								   ExpPtr condition, ExpPtr ifTrue)
	: Expression(line, column, ExpressionKind::IfThen)
	, condition{condition}
	, ifTrue{ifTrue}
{
}

IfThenElseExpression::IfThenElseExpression(int32_t line, int32_t column,
										   ExpPtr condition, ExpPtr ifTrue,
										   ExpPtr ifFalse)
	: Expression(line, column, ExpressionKind::IfThenElse)
	, condition{condition}
	, ifTrue{ifTrue}
	, ifFalse{ifFalse}
{
}

CallExpression::CallExpression(int32_t line, int32_t column, ExpPtr function,
							   vector<ExpPtr> arguments)
	: Expression(line, column, ExpressionKind::Call)
	, function{function}
	, arguments{arguments}
{
}

VariableExpression::VariableExpression(int32_t line, int32_t column,
									   wstring name)
	: Expression(line, column, ExpressionKind::Variable)
	, name{name}
{
}
ReturnExpression::ReturnExpression(int32_t line, int32_t column, ExpPtr value)
	: Expression(line, column, ExpressionKind::Return)
	, value{value}
{
}
WhileExpression::WhileExpression(int32_t line, int32_t column, ExpPtr condition,
								 ExpPtr body)
	: Expression(line, column, ExpressionKind::While)
	, condition{condition}
	, body{body}
{
}
DotExpression::DotExpression(int32_t line, int32_t column, ExpPtr object,
							 wstring name)
	: Expression(line, column, ExpressionKind::Dot)
	, object{object}
	, name{name}
{
}
void ConstantExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
void UnaryExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
void BinaryExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
void AssignExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
void BlockExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
void IfThenExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
void IfThenElseExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
void CallExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
void VariableExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
void ReturnExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
void WhileExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
void DotExpression::Accept(Expression::Visitor* visitor)
{
	visitor->Visit(this);
}
UnaryExpPtr Ast::UnaryPlus(int32_t line, int32_t column, ExpPtr operand)
{
	return make_shared<UnaryExpression>(line, column, ExpressionKind::UnaryPlus,
										operand);
}
UnaryExpPtr Ast::UnaryMinus(int32_t line, int32_t column, ExpPtr operand)
{
	return make_shared<UnaryExpression>(line, column,
										ExpressionKind::UnaryMinus, operand);
}
UnaryExpPtr Ast::Not(int32_t line, int32_t column, ExpPtr operand)
{
	return make_shared<UnaryExpression>(line, column, ExpressionKind::Not,
										operand);
}
BinaryExpPtr Ast::Add(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2)
{
	return make_shared<BinaryExpression>(line, column, ExpressionKind::Add, e1,
										 e2);
}
BinaryExpPtr Ast::Subtract(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2)
{
	return make_shared<BinaryExpression>(line, column, ExpressionKind::Subtract,
										 e1, e2);
}
BinaryExpPtr Ast::Multiply(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2)
{
	return make_shared<BinaryExpression>(line, column, ExpressionKind::Multiply,
										 e1, e2);
}
BinaryExpPtr Ast::Divide(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2)
{
	return make_shared<BinaryExpression>(line, column, ExpressionKind::Divide,
										 e1, e2);
}
BinaryExpPtr Ast::Modulo(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2)
{
	return make_shared<BinaryExpression>(line, column, ExpressionKind::Modulo,
										 e1, e2);
}
BinaryExpPtr Ast::GreaterThan(int32_t line, int32_t column, ExpPtr e1,
							  ExpPtr e2)
{
	return make_shared<BinaryExpression>(line, column,
										 ExpressionKind::GreaterThan, e1, e2);
}
BinaryExpPtr Ast::LessThan(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2)
{
	return make_shared<BinaryExpression>(line, column, ExpressionKind::LessThan,
										 e1, e2);
}
BinaryExpPtr Ast::GreaterThanOrEqual(int32_t line, int32_t column, ExpPtr e1,
									 ExpPtr e2)
{
	return make_shared<BinaryExpression>(
		line, column, ExpressionKind::GreaterThanOrEqual, e1, e2);
}
BinaryExpPtr Ast::LessThanOrEqual(int32_t line, int32_t column, ExpPtr e1,
								  ExpPtr e2)
{
	return make_shared<BinaryExpression>(
		line, column, ExpressionKind::LessThanOrEqual, e1, e2);
}
BinaryExpPtr Ast::Equal(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2)
{
	return make_shared<BinaryExpression>(line, column, ExpressionKind::Equal,
										 e1, e2);
}
BinaryExpPtr Ast::NotEqual(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2)
{
	return make_shared<BinaryExpression>(line, column, ExpressionKind::NotEqual,
										 e1, e2);
}
BinaryExpPtr Ast::And(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2)
{
	return make_shared<BinaryExpression>(line, column, ExpressionKind::And, e1,
										 e2);
}
BinaryExpPtr Ast::Or(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2)
{
	return make_shared<BinaryExpression>(line, column, ExpressionKind::Or, e1,
										 e2);
}
ConstantExpPtr Ast::Constant(int32_t line, int32_t column, std::any value)
{
	return make_shared<ConstantExpression>(line, column, value);
}
// DefVarExpPtr Ast::DefVar(int32_t line, int32_t column, AccessModifier
// modifier, 						 wstring name, Type type, ExpPtr value)
// {
// 	return make_shared<DefVarExpression>(line, column, modifier, name, type,
// 										 value);
// }
// DefFunExpPtr Ast::DefFun(int32_t line, int32_t column, AccessModifier
// modifier, 						 wstring name, vector<ParameterExpPtr>
// parameters, ExpPtr body, Type returnType)
// {
// 	return make_shared<DefFunExpression>(line, column, modifier, name,
// 										 parameters, body, returnType);
// }
CallExpPtr Ast::Call(int32_t line, int32_t column, ExpPtr function,
					 vector<ExpPtr> arguments)
{
	return make_shared<CallExpression>(line, column, function, arguments);
}
VariableExpPtr Ast::Variable(int32_t line, int32_t column, wstring name)
{
	return make_shared<VariableExpression>(line, column, name);
}
BlockExpPtr Ast::Block(int32_t line, int32_t column, vector<ExpPtr> expressions)
{
	return make_shared<BlockExpression>(line, column, expressions);
}
AssignExpPtr Ast::Assign(int32_t line, int32_t column, wstring name,
						 ExpPtr value)
{
	return make_shared<AssignExpression>(line, column, name, value);
}
IfThenExpPtr Ast::IfThen(int32_t line, int32_t column, ExpPtr condition,
						 ExpPtr ifTrue)
{
	return make_shared<IfThenExpression>(line, column, condition, ifTrue);
}
IfThenElseExpPtr Ast::IfThenElse(int32_t line, int32_t column, ExpPtr condition,
								 ExpPtr ifTrue, ExpPtr ifFalse)
{
	return make_shared<IfThenElseExpression>(line, column, condition, ifTrue,
											 ifFalse);
}
ReturnExpPtr Ast::Return(int32_t line, int32_t column, ExpPtr value)
{
	return make_shared<ReturnExpression>(line, column, value);
}
WhileExpPtr Ast::While(int32_t line, int32_t column, ExpPtr condition,
					   ExpPtr body)
{
	return make_shared<WhileExpression>(line, column, condition, body);
}
DotExpPtr Ast::Dot(int32_t line, int32_t column, ExpPtr object, wstring name)
{
	return make_shared<DotExpression>(line, column, object, name);
}
wstring ExpressionKindToString(ExpressionKind kind)
{
	switch (kind)
	{
	case ExpressionKind::Add:
		return L"Add";
	case ExpressionKind::Subtract:
		return L"Subtract";
	case ExpressionKind::Multiply:
		return L"Multiply";
	case ExpressionKind::Divide:
		return L"Divide";
	case ExpressionKind::Modulo:
		return L"Modulo";
	case ExpressionKind::GreaterThan:
		return L"GreaterThan";
	case ExpressionKind::LessThan:
		return L"LessThan";
	case ExpressionKind::GreaterThanOrEqual:
		return L"GreaterThanOrEqual";
	case ExpressionKind::LessThanOrEqual:
		return L"LessThanOrEqual";
	case ExpressionKind::Equal:
		return L"Equal";
	case ExpressionKind::NotEqual:
		return L"NotEqual";
	case ExpressionKind::Constant:
		return L"Constant";
	case ExpressionKind::UnaryPlus:
		return L"UnaryPlus";
	case ExpressionKind::UnaryMinus:
		return L"UnaryMinus";
	case ExpressionKind::And:
		return L"And";
	case ExpressionKind::Or:
		return L"Or";
	case ExpressionKind::Not:
		return L"Not";
	case ExpressionKind::IfThen:
		return L"IfThen";
	case ExpressionKind::IfThenElse:
		return L"IfThenElse";
	case ExpressionKind::Variable:
		return L"Variable";
	case ExpressionKind::Call:
		return L"Call";
	case ExpressionKind::Block:
		return L"Block";
	case ExpressionKind::Assign:
		return L"Assign";
	case ExpressionKind::Return:
		return L"Return";
	case ExpressionKind::While:
		return L"While";
	case ExpressionKind::Dot:
		return L"Dot";
	default:
		throw wstring(L"error");
	}
}