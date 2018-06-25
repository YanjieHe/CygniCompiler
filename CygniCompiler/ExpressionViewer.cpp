#include "ExpressionViewer.hpp"
#include <iostream>
using std::any_cast;
using std::endl;
using std::wcout;
ExpressionViewer::ExpressionViewer()
{
}
void ExpressionViewer::Visit(ConstantExpression* node)
{
	wcout << endl << L"(Constant ";
	any& value = node->value;
	if (value.type() == typeid(int32_t))
	{
		wcout << L"Int ";
		wcout << any_cast<int32_t>(value) << L")";
	}
	else if (value.type() == typeid(int64_t))
	{
		wcout << L"Long ";
		wcout << any_cast<int64_t>(value) << L")";
	}
	else if (value.type() == typeid(float))
	{
		wcout << L"Float ";
		wcout << any_cast<float>(value) << L")";
	}
	else if (value.type() == typeid(double))
	{
		wcout << L"Double ";
		wcout << any_cast<double>(value) << L")";
	}
	else if (value.type() == typeid(wchar_t))
	{
		wcout << L"Char ";
		wcout << any_cast<wchar_t>(value) << L")";
	}
	else if (value.type() == typeid(bool))
	{
		wcout << L"Boolean ";
		wcout << any_cast<bool>(value) << L")";
	}
	else if (value.type() == typeid(wstring))
	{
		wcout << L"String ";
		wcout << any_cast<wstring>(value) << L")";
	}
	else
	{
		wcout << L"Error )";
	}
}
void ExpressionViewer::Visit(UnaryExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	node->operand->Accept(this);
	wcout << L")";
}
void ExpressionViewer::Visit(BinaryExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	node->left->Accept(this);
	wcout << L" ";
	node->right->Accept(this);
	wcout << L")";
}
void ExpressionViewer::Visit(AssignExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	wcout << node->name << L" ";
	node->value->Accept(this);
	wcout << L")";
}
void ExpressionViewer::Visit(BlockExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	for (auto& e : node->expressions)
	{
		e->Accept(this);
	}
	wcout << L")";
}
void ExpressionViewer::Visit(IfThenExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	node->condition->Accept(this);
	wcout << L" ";
	node->ifTrue->Accept(this);
	wcout << L")";
}
void ExpressionViewer::Visit(IfThenElseExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	node->condition->Accept(this);
	wcout << L" ";
	node->ifTrue->Accept(this);
	wcout << L" ";
	node->ifFalse->Accept(this);
	wcout << L")";
}
void ExpressionViewer::Visit(DefVarExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	wcout << node->name << L" ";
	node->value->Accept(this);
	wcout << L")";
}
void ExpressionViewer::Visit(DefFunExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	wcout << node->name << L" ";
	for (auto& p : node->parameters)
	{
		p->Accept(this);
		wcout << L" ";
	}
	node->body->Accept(this);
	wcout << L")";
}
void ExpressionViewer::Visit(ParameterExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	wcout << node->name << L")";
}
void ExpressionViewer::Visit(CallExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	node->function->Accept(this);
	wcout << L" ";
	for (auto& arg : node->arguments)
	{
		arg->Accept(this);
		wcout << L" ";
	}
	wcout << L")";
}
void ExpressionViewer::Visit(VariableExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	wcout << node->name << L")";
}
void ExpressionViewer::Visit(ReturnExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	node->value->Accept(this);
	wcout << L")";
}
void ExpressionViewer::Visit(WhileExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	wcout << TypeToString(node->type) << L" ";
	node->condition->Accept(this);
	wcout << L" ";
	node->body->Accept(this);
	wcout << L")";
}