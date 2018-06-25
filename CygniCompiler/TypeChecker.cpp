#include "TypeChecker.hpp"
#include "Exception.hpp"
#include <iostream>
using std::any_cast;
using std::endl;
using std::wcout;
TypeChecker::TypeChecker()
	: global()
	, current{&global}
{
}
void TypeChecker::Visit(ConstantExpression* node)
{
	any& value = node->value;
	if (value.type() == typeid(int32_t))
	{
		node->type = Type::Int();
	}
	else if (value.type() == typeid(int64_t))
	{
		node->type = Type::Long();
	}
	else if (value.type() == typeid(float))
	{
		node->type = Type::Float();
	}
	else if (value.type() == typeid(double))
	{
		node->type = Type::Double();
	}
	else if (value.type() == typeid(wchar_t))
	{
		node->type = Type::Char();
	}
	else if (value.type() == typeid(bool))
	{
		node->type = Type::Boolean();
	}
	else if (value.type() == typeid(wstring))
	{
		node->type = Type::String();
	}
	else
	{
		throw wstring(L"error");
	}
}
void TypeChecker::Visit(UnaryExpression* node)
{
	node->operand->Accept(this);
	if (node->kind == ExpressionKind::UnaryPlus)
	{
		if (node->operand->type.IsInt() || node->operand->type.IsLong() ||
			node->operand->type.IsFloat() || node->operand->type.IsDouble())
		{
			node->type = node->operand->type;
		}
		else
		{
			throw TypeException(
				node->line, node->column,
				L"The '+' operator cannot be applied to operand of type " +
					TypeToString(node->operand->type));
		}
	}
	else if (node->kind == ExpressionKind::UnaryMinus)
	{
		if (node->operand->type.IsInt() || node->operand->type.IsLong() ||
			node->operand->type.IsFloat() || node->operand->type.IsDouble())
		{
			node->type = node->operand->type;
		}
		else
		{
			throw TypeException(
				node->line, node->column,
				L"The '-' operator cannot be applied to operand of type " +
					TypeToString(node->operand->type));
		}
	}
	else if (node->kind == ExpressionKind::Not)
	{
		if (node->operand->type.IsBoolean())
		{
			node->type = node->operand->type;
		}
		else
		{
			throw TypeException(
				node->line, node->column,
				L"The 'not' operator cannot be applied to operand of type " +
					TypeToString(node->operand->type));
		}
	}
	else
	{
		throw wstring(L"error");
	}
}
void TypeChecker::Visit(BinaryExpression* node)
{
	node->left->Accept(this);
	node->right->Accept(this);
	Type& left = node->left->type;
	Type& right = node->right->type;
	ExpressionKind kind = node->kind;
	if (kind == ExpressionKind::Add || kind == ExpressionKind::Subtract ||
		kind == ExpressionKind::Multiply || kind == ExpressionKind::Divide)
	{
		if (left.IsInt() && right.IsInt())
		{
			node->type = Type::Int();
		}
		else if (left.IsDouble() && right.IsDouble())
		{
			node->type = Type::Double();
		}
		else if (left.IsFloat() && right.IsFloat())
		{
			node->type = Type::Float();
		}
		else if (left.IsLong() && right.IsLong())
		{
			node->type = Type::Long();
		}
		else
		{
			throw TypeException(node->line, node->column,
								L"Operator `-' cannot be applied to operands "
								L"of type '" +
									TypeToString(left) + L"' and '" +
									TypeToString(right) + L"'");
		}
	}
	else if (kind == ExpressionKind::Modulo)
	{
		if (left.IsInt() && right.IsInt())
		{
			node->type = Type::Int();
		}
		else if (left.IsLong() && right.IsLong())
		{
			node->type = Type::Long();
		}
		else
		{
			throw TypeException(node->line, node->column,
								L"Operator cannot be applied to operands "
								L"of type '" +
									TypeToString(left) + L"' and '" +
									TypeToString(right) + L"'");
		}
	}
	else if (kind == ExpressionKind::GreaterThan ||
			 kind == ExpressionKind::LessThan ||
			 kind == ExpressionKind::GreaterThanOrEqual ||
			 kind == ExpressionKind::LessThanOrEqual)
	{
		if (left.IsInt() && right.IsInt())
		{
			node->type = Type::Boolean();
		}
		else if (left.IsDouble() && right.IsDouble())
		{
			node->type = Type::Boolean();
		}
		else if (left.IsLong() && right.IsLong())
		{
			node->type = Type::Boolean();
		}
		else if (left.IsFloat() && right.IsFloat())
		{
			node->type = Type::Boolean();
		}
		else
		{
			throw TypeException(node->line, node->column,
								L"Operator cannot be applied to operands "
								L"of type '" +
									TypeToString(left) + L"' and '" +
									TypeToString(right) + L"'");
		}
	}
	else if (kind == ExpressionKind::And || kind == ExpressionKind::Or)
	{
		if (left.IsBoolean() && right.IsBoolean())
		{
			node->type = Type::Boolean();
		}
		else
		{
			throw TypeException(node->line, node->column,
								L"Operator cannot be applied to operands "
								L"of type '" +
									TypeToString(left) + L"' and '" +
									TypeToString(right) + L"'");
		}
	}
	else if (kind == ExpressionKind::Equal || kind == ExpressionKind::NotEqual)
	{
		if (left.IsInt() && right.IsInt())
		{
			node->type = Type::Boolean();
		}
		else if (left.IsDouble() && right.IsDouble())
		{
			node->type = Type::Boolean();
		}
		else if (left.IsBoolean() && right.IsBoolean())
		{
			node->type = Type::Boolean();
		}
		else if (left.IsChar() && right.IsChar())
		{
			node->type = Type::Boolean();
		}
		else if (left.IsString() && right.IsString())
		{
			node->type = Type::Boolean();
		}
		else
		{
			throw TypeException(node->line, node->column,
								L"Operator cannot be applied to operands "
								L"of type '" +
									TypeToString(left) + L"' and '" +
									TypeToString(right) + L"'");
		}
	}
	else
	{
		throw TypeException(node->line, node->column,
							L"Operator cannot be applied to operands "
							L"of type '" +
								TypeToString(left) + L"' and '" +
								TypeToString(right) + L"'");
	}
}
void TypeChecker::Visit(AssignExpression* node)
{
	node->value->Accept(this);
	if (current->HasSymbol(node->name))
	{
		Symbol symbol = current->Find(node->name);
		if (symbol.kind == SymbolKind::VariableSymbol)
		{
			Type type = any_cast<Type>(symbol.value);
			if (type == node->value->type)
			{
				node->type = type;
			}
			else
			{
				throw TypeException(node->line, node->column,
									L"Cannot implicitly convert type `" +
										TypeToString(node->value->type) +
										L" to '" + TypeToString(type) + L"'");
			}
		}
		else
		{
			throw TypeException(node->line, node->column,
								L"name '" + node->name +
									L"' is not a variable");
		}
	}
	else
	{
		throw TypeException(node->line, node->column,
							L"name '" + node->name + L"' is not defined");
	}
}
void TypeChecker::Visit(BlockExpression* node)
{
	for (ExpPtr& exp : node->expressions)
	{
		exp->Accept(this);
	}
	node->type = Type::Unit();
}
void TypeChecker::Visit(IfThenExpression* node)
{
	node->condition->Accept(this);
	if (node->condition->type.IsBoolean())
	{
		node->ifTrue->Accept(this);
		node->type = Type::Unit();
	}
	else
	{
		throw TypeException(node->line, node->column,
							L"value cannot be converted to 'Boolean'");
	}
}
void TypeChecker::Visit(IfThenElseExpression* node)
{
	node->condition->Accept(this);
	if (node->condition->type.IsBoolean())
	{
		node->ifTrue->Accept(this);
		node->ifFalse->Accept(this);
		node->type = Type::Unit();
	}
	else
	{
		throw TypeException(node->line, node->column,
							L"value cannot be converted to 'Boolean'");
	}
}
void TypeChecker::Visit(DefVarExpression* node)
{
	node->value->Accept(this);
	Type& rtype = node->value->type;
	if (node->type == rtype)
	{
		current->Put(node->name,
					 Symbol(SymbolKind::VariableSymbol, node->type));
	}
	else
	{
		throw TypeException(node->line, node->column,
							L"Cannot implicitly convert type '" +
								TypeToString(node->type) + L"' to '" +
								TypeToString(rtype) + L"'");
	}
}
void TypeChecker::Visit(DefFunExpression* node)
{
	SymbolTable* prev = current;
	SymbolTable newTable(prev);
	current = &newTable;
	current->Put(node->name, Symbol(SymbolKind::FunctionSymbol, node->type));
	for (ParameterExpPtr& p : node->parameters)
	{
		current->Put(p->name, Symbol(SymbolKind::VariableSymbol, p->type));
	}
	node->body->Accept(this);
	current = prev;
}
void TypeChecker::Visit(ParameterExpression*)
{
	throw wstring(L"not implemented");
}
void TypeChecker::Visit(CallExpression* node)
{
	node->function->Accept(this);
	for (ExpPtr& arg : node->arguments)
	{
		arg->Accept(this);
	}
	if (node->function->type.IsFunction())
	{
		vector<Type>& types = node->function->type.parameters;
		if (types.size() == node->arguments.size() + 1)
		{
			int n = node->arguments.size();
			for (int i = 0; i < n; i++)
			{
				if (types.at(i) != node->arguments.at(i)->type)
				{
					throw TypeException(node->line, node->column,
										L"argument type does not match");
				}
			}
			node->type = types.back();
		}
		else
		{
			throw TypeException(node->line, node->column,
								L"argument count does not match");
		}
	}
	else
	{
		throw TypeException(node->line, node->column,
							L"object cannot be used as function");
	}
}
void TypeChecker::Visit(VariableExpression* node)
{
	if (current->HasSymbol(node->name))
	{
		Symbol symbol = current->Find(node->name);
		if (symbol.kind == SymbolKind::VariableSymbol)
		{
			Type type = any_cast<Type>(symbol.value);
			node->type = type;
		}
		else if (symbol.kind == SymbolKind::FunctionSymbol)
		{
			Type type = any_cast<Type>(symbol.value);
			node->type = type;
		}
		else
		{
			throw TypeException(node->line, node->column,
								L"name '" + node->name +
									L"' is not a variable");
		}
	}
	else
	{
		throw TypeException(node->line, node->column,
							L"name '" + node->name + L"' is not defined");
	}
}
void TypeChecker::Visit(ReturnExpression* node)
{
	node->value->Accept(this);
	node->type = node->value->type;
}
void TypeChecker::Visit(WhileExpression* node)
{
	node->condition->Accept(this);
	if (node->condition->type.IsBoolean())
	{
		node->body->Accept(this);
		node->type = Type::Unit();
	}
	else
	{
		throw TypeException(node->line, node->column,
							L"value cannot be converted to 'Boolean'");
	}
}