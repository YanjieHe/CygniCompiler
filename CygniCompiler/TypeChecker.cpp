#include "TypeChecker.hpp"
#include "Exception.hpp"
#include <iostream>
using std::any_cast;
using std::endl;
using std::wcout;

TypeChecker::TypeChecker(NamespaceRecord& nsRecord)
	: nsRecord{nsRecord}
{
	Scope globalScope(nullptr);
	scope = &globalScope;
	int32_t moduleCount = 0;
	int32_t classCount = 0;
	for (auto& pair : nsRecord.record)
	{
		auto& nsPtr = pair.second;
		Collect(nsPtr, moduleCount, classCount);
	}
	for (auto& pair : nsRecord.record)
	{
		auto& nsPtr = pair.second;
		Check(nsPtr);
	}
}
void TypeChecker::Check(shared_ptr<Namespace> nsPtr)
{
	Scope nextScope(scope);
	Scope* parent = scope;
	scope = &nextScope;
	for (auto& pair : nsPtr->modules)
	{
		Module& moduleInfo = pair.second;
		CheckModule(moduleInfo);
	}
	for (auto& pair : nsPtr->classes)
	{
		Class& classInfo = pair.second;
		CheckClass(classInfo);
	}
	scope = parent;
}
void TypeChecker::CheckModule(Module& moduleInfo)
{
	Scope nextScope(scope);
	Scope* parent = scope;
	scope = &nextScope;
	for (auto& field : moduleInfo.fields)
	{
		CheckField(field);
	}
	for (auto& function : moduleInfo.functions)
	{
		CheckFunction(function);
	}
	scope = parent;
}
void TypeChecker::CheckClass(Class& classInfo)
{
	Scope nextScope(scope);
	Scope* parent = scope;
	scope = &nextScope;
	for (auto& field : classInfo.fields)
	{
		CheckField(field);
	}
	for (auto& function : classInfo.functions)
	{
		CheckFunction(function);
	}
	scope = parent;
}
void TypeChecker::CheckField(Field& field)
{
	field.value->Accept(this);
	if (field.value->type != field.type)
	{
		throw TypeException(field.value->line, field.value->column,
							L"Cannot implicitly convert type `" +
								TypeToString(field.value->type) + L" to '" +
								TypeToString(field.type) + L"'");
	}
}
void TypeChecker::CheckFunction(Function& function)
{
	Scope nextScope(scope);
	Scope* parent = scope;
	scope = &nextScope;
	for (Parameter& p : function.parameters)
	{
		scope->Put(p.name, p);
	}
	for (LocalVariable& v : function.variables)
	{
		scope->Put(v.name, v);
	}
	for (LocalVariable& v : function.variables)
	{
		v.value->Accept(this);
	}
	for (ExpPtr& e : function.expressions)
	{
		e->Accept(this);
	}
	scope = parent;
}
void TypeChecker::Collect(shared_ptr<Namespace> nsPtr, int32_t moduleCount,
						  int32_t classCount)
{
	for (auto& pair : nsPtr->modules)
	{
		Module& moduleInfo = pair.second;
		moduleInfo.index = moduleCount;
		moduleCount++;
		scope->Put(moduleInfo.type.name, moduleInfo);
		int32_t fieldOffset = 0;
		int32_t functionOffset = 0;
		for (Field& field : moduleInfo.fields)
		{
			field.location = Location(moduleInfo.index, fieldOffset);
			fieldOffset++;
			scope->Put(field.name, field);
		}
		for (Function& function : moduleInfo.functions)
		{
			function.location = Location(moduleInfo.index, functionOffset);
			functionOffset++;
			scope->Put(function.name, function);
			int32_t offset = 0;
			for (Parameter& p : function.parameters)
			{
				p.location = Location(-1, offset);
				offset++;
			}
			for (LocalVariable& v : function.variables)
			{
				v.location = Location(-1, offset);
				offset++;
			}
		}
	}
	for (auto& pair : nsPtr->classes)
	{
		Class& classInfo = pair.second;
		classInfo.index = classCount;
		classCount++;
		scope->Put(classInfo.type.name, classInfo);
		int32_t fieldOffset = 0;
		int32_t functionOffset = 0;
		for (Field& field : classInfo.fields)
		{
			field.location = Location(classInfo.index, fieldOffset);
			fieldOffset++;
			scope->Put(field.name, field);
		}
		for (Function& function : classInfo.functions)
		{
			function.location = Location(classInfo.index, functionOffset);
			functionOffset++;
			scope->Put(function.name, function);
			int32_t offset = 0;
			for (Parameter& p : function.parameters)
			{
				p.location = Location(-1, offset);
				offset++;
			}
			for (LocalVariable& v : function.variables)
			{
				v.location = Location(-1, offset);
				offset++;
			}
		}
	}
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
			throw TypeException(node->line, node->column,
								L"The 'not' operator cannot be applied to "
								L"operand of type " +
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
		else if (left.IsLong() && right.IsLong())
		{
			node->type = Type::Boolean();
		}
		else if (left.IsFloat() && right.IsFloat())
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
	if (scope->Contains(node->name))
	{
		any value = scope->Get(node->name);
		if (value.type() == typeid(LocalVariable))
		{
			LocalVariable variable = any_cast<LocalVariable>(value);
			node->type = variable.type;
			if (node->type == node->value->type)
			{
			}
			else
			{
				throw TypeException(node->line, node->column,
									L"Cannot implicitly convert type `" +
										TypeToString(node->value->type) +
										L" to '" + TypeToString(node->type) +
										L"'");
			}
			node->location = variable.location;
		}
		else if (value.type() == typeid(Field))
		{
			Field field = any_cast<Field>(value);
			node->type = field.type;
			if (node->type == node->value->type)
			{
			}
			else
			{
				throw TypeException(node->line, node->column,
									L"Cannot implicitly convert type `" +
										TypeToString(node->value->type) +
										L" to '" + TypeToString(node->type) +
										L"'");
			}
			node->location = field.location;
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
			int32_t n = node->arguments.size();
			for (int32_t i = 0; i < n; i++)
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
	if (scope->Contains(node->name))
	{
		any value = scope->Get(node->name);
		if (value.type() == typeid(LocalVariable))
		{
			LocalVariable variable = any_cast<LocalVariable>(value);
			node->type = variable.type;
			node->location = variable.location;
		}
		else if (value.type() == typeid(Parameter))
		{
			Parameter parameter = any_cast<Parameter>(value);
			node->type = parameter.type;
			node->location = parameter.location;
		}
		else if (value.type() == typeid(Field))
		{
			Field field = any_cast<Field>(value);
			node->type = field.type;
			node->location = field.location;
		}
		else if (value.type() == typeid(Function))
		{
			Function function = any_cast<Function>(value);
			node->type = function.functionType;
			node->location = function.location;
		}
		else if (value.type() == typeid(Module))
		{
			node->type = any_cast<Module>(value).type;
		}
		else if (value.type() == typeid(Class))
		{
			node->type = any_cast<Class>(value).type;
		}
		else
		{
			throw wstring(L"not supported type");
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
void TypeChecker::Visit(DotExpression* node)
{
	node->object->Accept(this);
	Type& objType = node->object->type;
	if (objType.IsModule())
	{
		Module moduleInfo = any_cast<Module>(scope->Get(objType.name));
		if (moduleInfo.fieldMap.find(node->name) != moduleInfo.fieldMap.end())
		{
			node->type = moduleInfo.fieldMap[node->name].type;
		}
		else if (moduleInfo.functionMap.find(node->name) !=
				 moduleInfo.functionMap.end())
		{
			node->type = moduleInfo.functionMap[node->name].functionType;
		}
		else
		{
			throw TypeException(node->line, node->column, L"field not defined");
		}
	}
	else if (objType.IsClass())
	{
		Class classInfo = any_cast<Class>(scope->Get(objType.name));
		if (classInfo.fieldMap.find(node->name) != classInfo.fieldMap.end())
		{
			node->type = classInfo.fieldMap[node->name].type;
		}
		else if (classInfo.functionMap.find(node->name) !=
				 classInfo.functionMap.end())
		{
			node->type = classInfo.functionMap[node->name].functionType;
		}
		else
		{
			throw TypeException(node->line, node->column, L"field not defined");
		}
	}
	else
	{
		throw TypeException(node->line, node->column, L"error type");
	}
}