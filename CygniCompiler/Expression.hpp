#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include "Type.hpp"
#include <any>
#include <memory>
#include <string>
#include <vector>
using std::any;
using std::shared_ptr;
using std::vector;
using std::wstring;

class Expression;
class ConstantExpression;
class UnaryExpression;
class BinaryExpression;
class AssignExpression;
class BlockExpression;
class IfThenExpression;
class IfThenElseExpression;
class DefVarExpression;
class DefFunExpression;
class ParameterExpression;
class CallExpression;
class VariableExpression;
class ReturnExpression;
class WhileExpression;

using ExpPtr = shared_ptr<Expression>;
using ConstantExpPtr = shared_ptr<ConstantExpression>;
using UnaryExpPtr = shared_ptr<UnaryExpression>;
using BinaryExpPtr = shared_ptr<BinaryExpression>;
using AssignExpPtr = shared_ptr<AssignExpression>;
using BlockExpPtr = shared_ptr<BlockExpression>;
using IfThenExpPtr = shared_ptr<IfThenExpression>;
using IfThenElseExpPtr = shared_ptr<IfThenElseExpression>;
using DefVarExpPtr = shared_ptr<DefVarExpression>;
using DefFuncExpPtr = shared_ptr<DefFunExpression>;
using ParameterExpPtr = shared_ptr<ParameterExpression>;
using CallExpPtr = shared_ptr<CallExpression>;
using VariableExpPtr = shared_ptr<VariableExpression>;
using ReturnExpPtr = shared_ptr<ReturnExpression>;
using WhileExpPtr = shared_ptr<WhileExpression>;

enum class ExpressionKind
{
	Add,
	Subtract,
	Multiply,
	Divide,
	Modulo,

	GreaterThan,
	LessThan,
	GreaterThanOrEqual,
	LessThanOrEqual,
	Equal,
	NotEqual,
	Constant,
	UnaryPlus,
	UnaryMinus,

	And,
	Or,
	Not,

	DefVar,
	DefFun,
	IfThen,
	IfThenElse,
	Parameter,
	Variable,
	Call,
	Block,
	Assign,

	Return,
	While
};
class Expression
{
public:
	int32_t line;
	int32_t column;
	ExpressionKind kind;
	Type type;
	Expression(int32_t line, int32_t column, ExpressionKind kind);

	class Visitor
	{
	public:
		virtual void Visit(ConstantExpression* node) = 0;
		virtual void Visit(UnaryExpression* node) = 0;
		virtual void Visit(BinaryExpression* node) = 0;
		virtual void Visit(AssignExpression* node) = 0;
		virtual void Visit(BlockExpression* node) = 0;
		virtual void Visit(IfThenExpression* node) = 0;
		virtual void Visit(IfThenElseExpression* node) = 0;
		virtual void Visit(DefVarExpression* node) = 0;
		virtual void Visit(DefFunExpression* node) = 0;
		virtual void Visit(ParameterExpression* node) = 0;
		virtual void Visit(CallExpression* node) = 0;
		virtual void Visit(VariableExpression* node) = 0;
		virtual void Visit(ReturnExpression* node) = 0;
		virtual void Visit(WhileExpression* node) = 0;
	};
	virtual void Accept(Visitor* visitor) = 0;
};
class ConstantExpression : public Expression
{
public:
	any value;
	ConstantExpression(int32_t line, int32_t column, any value);
	void Accept(Visitor* visitor) override;
};

class UnaryExpression : public Expression
{
public:
	ExpPtr operand;
	UnaryExpression(int32_t line, int32_t column, ExpressionKind kind,
					ExpPtr operand);
	void Accept(Visitor* visitor) override;
};

class BinaryExpression : public Expression
{
public:
	ExpPtr left;
	ExpPtr right;
	BinaryExpression(int32_t line, int32_t column, ExpressionKind kind,
					 ExpPtr left, ExpPtr right);
	void Accept(Visitor* visitor) override;
};

class AssignExpression : public Expression
{
public:
	wstring name;
	ExpPtr value;
	AssignExpression(int32_t line, int32_t column, wstring name, ExpPtr value);
	void Accept(Visitor* visitor) override;
};

class BlockExpression : public Expression
{
public:
	vector<ExpPtr> expressions;
	BlockExpression(int32_t line, int32_t column, vector<ExpPtr> expressions);
	void Accept(Visitor* visitor) override;
};

class IfThenExpression : public Expression
{
public:
	ExpPtr condition;
	ExpPtr ifTrue;
	IfThenExpression(int32_t line, int32_t column, ExpPtr condition,
					 ExpPtr ifTrue);
	void Accept(Visitor* visitor) override;
};

class IfThenElseExpression : public Expression
{
public:
	ExpPtr condition;
	ExpPtr ifTrue;
	ExpPtr ifFalse;
	IfThenElseExpression(int32_t line, int32_t column, ExpPtr condition,
						 ExpPtr ifTrue, ExpPtr ifFalse);
	void Accept(Visitor* visitor) override;
};

class DefVarExpression : public Expression
{
public:
	wstring name;
	ExpPtr value;
	DefVarExpression(int32_t line, int32_t column, wstring name, Type type,
					 ExpPtr value);
	void Accept(Visitor* visitor) override;
};

class DefFunExpression : public Expression
{
public:
	wstring name;
	vector<ParameterExpPtr> parameters;
	ExpPtr body;
	Type returnType;
	DefFunExpression(int32_t line, int32_t column, wstring name,
					 vector<ParameterExpPtr> parameters, ExpPtr body,
					 Type returnType);
	void Accept(Visitor* visitor) override;
};

class ParameterExpression : public Expression
{
public:
	wstring name;
	ParameterExpression(int32_t line, int32_t column, wstring name, Type type);
	void Accept(Visitor* visitor) override;
};

class CallExpression : public Expression
{
public:
	ExpPtr function;
	vector<ExpPtr> arguments;
	CallExpression(int32_t line, int32_t column, ExpPtr function,
				   vector<ExpPtr> arguments);
	void Accept(Visitor* visitor) override;
};

class VariableExpression : public Expression
{
public:
	wstring name;
	VariableExpression(int32_t line, int32_t column, wstring name);
	void Accept(Visitor* visitor) override;
};

class ReturnExpression : public Expression
{
public:
	ExpPtr value;
	ReturnExpression(int32_t line, int32_t column, ExpPtr value);
	void Accept(Visitor* visitor) override;
};

class WhileExpression : public Expression
{
public:
	ExpPtr condition;
	ExpPtr body;
	WhileExpression(int32_t line, int32_t column, ExpPtr condition,
					ExpPtr body);
	void Accept(Visitor* visitor) override;
};
namespace Ast
{
UnaryExpPtr UnaryPlus(int32_t line, int32_t column, ExpPtr operand);
UnaryExpPtr UnaryMinus(int32_t line, int32_t column, ExpPtr operand);
UnaryExpPtr Not(int32_t line, int32_t column, ExpPtr operand);
BinaryExpPtr Add(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2);
BinaryExpPtr Subtract(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2);
BinaryExpPtr Multiply(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2);
BinaryExpPtr Divide(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2);
BinaryExpPtr Modulo(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2);
BinaryExpPtr GreaterThan(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2);
BinaryExpPtr LessThan(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2);
BinaryExpPtr GreaterThanOrEqual(int32_t line, int32_t column, ExpPtr e1,
								ExpPtr e2);
BinaryExpPtr LessThanOrEqual(int32_t line, int32_t column, ExpPtr e1,
							 ExpPtr e2);
BinaryExpPtr Equal(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2);
BinaryExpPtr NotEqual(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2);
BinaryExpPtr And(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2);
BinaryExpPtr Or(int32_t line, int32_t column, ExpPtr e1, ExpPtr e2);
ConstantExpPtr Constant(int32_t line, int32_t column, any value);
DefVarExpPtr DefineVariable(int32_t line, int32_t column, wstring name,
							Type type, ExpPtr value);
DefFuncExpPtr DefineFunction(int32_t line, int32_t column, wstring name,
							 vector<ParameterExpPtr> parameters, ExpPtr body,
							 Type returnType);
CallExpPtr Call(int32_t line, int32_t column, ExpPtr function,
				vector<ExpPtr> arguments);
VariableExpPtr Variable(int32_t line, int32_t column, wstring name);
BlockExpPtr Block(int32_t line, int32_t column, vector<ExpPtr> expressions);
AssignExpPtr Assign(int32_t line, int32_t column, wstring name, ExpPtr value);
IfThenExpPtr IfThen(int32_t line, int32_t column, ExpPtr condition,
					ExpPtr ifTrue);
IfThenElseExpPtr IfThenElse(int32_t line, int32_t column, ExpPtr condition,
							ExpPtr ifTrue, ExpPtr ifFalse);
ParameterExpPtr Parameter(int32_t line, int32_t column, wstring name,
						  Type type);
ReturnExpPtr Return(int32_t line, int32_t column, ExpPtr value);
WhileExpPtr While(int32_t line, int32_t column, ExpPtr condition, ExpPtr body);
} // namespace Ast

wstring ExpressionKindToString(ExpressionKind kind);
#endif // EXPRESSION_HPP