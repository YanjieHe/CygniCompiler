#include "ExpressionViewer.hpp"
#include <iostream>
using std::any_cast;
using std::endl;
using std::wcout;
ExpressionViewer::ExpressionViewer()
{
}
void ExpressionViewer::ViewNamespace(shared_ptr<Namespace> nsPtr)
{
	for (auto& pair : nsPtr->modules)
	{
		auto& moduleInfo = pair.second;
		for (auto& field : moduleInfo.fields)
		{
			wcout << L"(var ";
			wcout << field.name << L" ";
			field.value->Accept(this);
			wcout << L")";
		}
		for (auto& function : moduleInfo.functions)
		{
			wcout << L"(fun ";
			wcout << function.name << L" ";
			wcout << L"(";
			for (auto& parameter : function.parameters)
			{
				wcout << parameter.name << L" ";
				wcout << TypeToString(parameter.type) << L" ";
			}
			wcout << L")" << endl;
			for (auto& variable : function.variables)
			{
				wcout << L"(var ";
				wcout << variable.name << L" ";
				variable.value->Accept(this);
				wcout << L")";
			}
			for (auto& e : function.expressions)
			{
				e->Accept(this);
			}
			wcout << L")" << endl;
		}
	}
	for (auto& pair : nsPtr->classes)
	{
		auto& classInfo = pair.second;
		for (auto& field : classInfo.fields)
		{
			wcout << L"(var ";
			wcout << field.name << L" ";
			field.value->Accept(this);
			wcout << L")";
		}
		for (auto& function : classInfo.functions)
		{
			for (auto& e : function.expressions)
			{
				e->Accept(this);
			}
		}
	}
	for (auto& pair : nsPtr->subNamespaces)
	{
		auto& subNsPtr = pair.second;
		ViewNamespace(subNsPtr);
	}
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
void ExpressionViewer::Visit(DotExpression* node)
{
	wcout << endl << L"(" << ExpressionKindToString(node->kind) << L" ";
	node->object->Accept(this);
	wcout << L" ";
	wcout << node->name << L")";
}