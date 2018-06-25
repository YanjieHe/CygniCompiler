#include "ConstantCollector.hpp"
using std::any_cast;
ConstantCollector::ConstantCollector()
{
}
void ConstantCollector::Visit(ConstantExpression* node)
{
	any& value = node->value;
	if (value.type() == typeid(wstring))
	{
		wstring text = any_cast<wstring>(value);
		bool found = stringTable.find(text) != stringTable.end();
		if (!found)
		{
			int index = stringTable.size();
			stringTable.insert({text, index});
		}
	}
}
void ConstantCollector::Visit(UnaryExpression* node)
{
	node->operand->Accept(this);
}
void ConstantCollector::Visit(BinaryExpression* node)
{
	node->left->Accept(this);
	node->right->Accept(this);
}
void ConstantCollector::Visit(AssignExpression* node)
{
	node->value->Accept(this);
}
void ConstantCollector::Visit(BlockExpression* node)
{
	for (auto& e : node->expressions)
	{
		e->Accept(this);
	}
}
void ConstantCollector::Visit(IfThenExpression* node)
{
	node->condition->Accept(this);
	node->ifTrue->Accept(this);
}
void ConstantCollector::Visit(IfThenElseExpression* node)
{
	node->condition->Accept(this);
	node->ifTrue->Accept(this);
	node->ifFalse->Accept(this);
}
void ConstantCollector::Visit(DefVarExpression* node)
{
	node->value->Accept(this);
}
void ConstantCollector::Visit(DefFunExpression* node)
{
	table.Put(node->name, Symbol(SymbolKind::FunctionSymbol, node->type));
	node->body->Accept(this);
}
void ConstantCollector::Visit(ParameterExpression*)
{
}
void ConstantCollector::Visit(CallExpression* node)
{
	node->function->Accept(this);
	for (auto& arg : node->arguments)
	{
		arg->Accept(this);
	}
}
void ConstantCollector::Visit(VariableExpression*)
{
}
void ConstantCollector::Visit(ReturnExpression* node)
{
	node->value->Accept(this);
}
void ConstantCollector::Visit(WhileExpression* node)
{
	node->condition->Accept(this);
	node->body->Accept(this);
}