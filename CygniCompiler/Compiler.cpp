#include "Compiler.hpp"
#include "Exception.hpp"
#include "Instruction.hpp"
#include <iostream>
using std::any_cast;
using std::endl;
using std::wcout;
Compiler::Compiler()
{
}
CompiledProgram Compiler::Compile(NamespaceRecord& nsRecord)
{
	for (auto& p : nsRecord.record)
	{
		auto& nsPtr = p.second;
		CompileNamespace(nsPtr);
	}
	return CompiledProgram(modules, classes);
}
void Compiler::CompileNamespace(shared_ptr<Namespace>& nsPtr)
{
	for (auto& p : nsPtr->modules)
	{
		Module& moduleInfo = p.second;
		vector<CompiledFunction> cfVec;
		for (auto& field : moduleInfo.fields)
		{
			field.value->Accept(this);
		}
		for (auto& function : moduleInfo.functions)
		{
			CompiledFunction cf = CompileFunction(function);
			cfVec.push_back(cf);
		}
		modules.push_back(
			CompiledModule(moduleInfo.index, moduleInfo.fields.size(), cfVec));
	}
	for (auto& p : nsPtr->classes)
	{
		Class& classInfo = p.second;
		vector<CompiledFunction> cfVec;
		for (auto& field : classInfo.fields)
		{
			field.value->Accept(this);
		}
		for (auto& function : classInfo.functions)
		{
			CompiledFunction cf = CompileFunction(function);
			cfVec.push_back(cf);
		}
		classes.push_back(
			CompiledClass(classInfo.index, classInfo.fields.size(), cfVec));
	}
	for (auto& p : nsPtr->subNamespaces)
	{
		auto& subNsPtr = p.second;
		CompileNamespace(subNsPtr);
	}
}
CompiledFunction Compiler::CompileFunction(Function& function)
{
	byteCode = ByteCode();
	constantPool = ByteCode();
	constantsCount = 0;
	for (LocalVariable& variable : function.variables)
	{
		variable.value->Accept(this);
		int32_t offset = variable.location.offset;
		if (variable.type.IsInt())
		{
			byteCode.push_back(pop_local_int);
		}
		else if (variable.type.IsLong())
		{
			byteCode.push_back(pop_local_long);
		}
		else if (variable.type.IsFloat())
		{
			byteCode.push_back(pop_local_float);
		}
		else if (variable.type.IsDouble())
		{
			byteCode.push_back(pop_local_double);
		}
		else if (variable.type.IsString())
		{
			byteCode.push_back(pop_local_string);
		}
		else
		{
			throw wstring(L"not supported variable type");
		}
		byteCode.push_back(offset);
	}
	for (auto& e : function.expressions)
	{
		e->Accept(this);
	}
	int32_t offset = function.location.offset;
	int32_t stackSize = 0;
	int32_t argsCount = function.parameters.size();
	int32_t localsCount = function.variables.size();
	return CompiledFunction(function.name, offset, stackSize, argsCount,
							localsCount, constantsCount, constantPool,
							byteCode);
}
void Compiler::Visit(ConstantExpression* node)
{
	any value = node->value;
	if (value.type() == typeid(int32_t))
	{
		constantPool.push_back(constant_int);
		ConvertInt(constantPool, any_cast<int32_t>(value));
		byteCode.push_back(push_constant_int);
	}
	else if (value.type() == typeid(int64_t))
	{
		constantPool.push_back(constant_long);
		ConvertLong(constantPool, any_cast<int64_t>(value));
		byteCode.push_back(push_constant_long);
	}
	else if (value.type() == typeid(float))
	{
		constantPool.push_back(constant_float);
		ConvertFloat(constantPool, any_cast<float>(value));
		byteCode.push_back(push_constant_float);
	}
	else if (value.type() == typeid(double))
	{
		constantPool.push_back(constant_double);
		ConvertDouble(constantPool, any_cast<double>(value));
		byteCode.push_back(push_constant_double);
	}
	else if (value.type() == typeid(wchar_t))
	{
		constantPool.push_back(constant_int);
		ConvertInt(constantPool, any_cast<int32_t>(value));
		byteCode.push_back(push_constant_int);
	}
	else if (value.type() == typeid(wstring))
	{
		constantPool.push_back(constant_string);
		ConvertString(constantPool, any_cast<wstring>(value));
		byteCode.push_back(push_constant_string);
	}
	else
	{
		throw wstring(L"wrong constant");
	}
	byteCode.push_back(constantsCount);
	constantsCount++;
}
void Compiler::Visit(UnaryExpression* node)
{
	node->operand->Accept(this);
	if (node->type.IsInt())
	{
		if (node->kind == ExpressionKind::UnaryPlus)
		{
		}
		else if (node->kind == ExpressionKind::UnaryMinus)
		{
			byteCode.push_back(minus_int);
		}
		else
		{
			throw wstring(L"wrong unary operation, where operand is int");
		}
	}
	else if (node->type.IsLong())
	{
		if (node->kind == ExpressionKind::UnaryPlus)
		{
		}
		else if (node->kind == ExpressionKind::UnaryMinus)
		{
			byteCode.push_back(minus_long);
		}
		else
		{
			throw wstring(L"wrong unary operation, where operand is long");
		}
	}
	else if (node->type.IsFloat())
	{
		if (node->kind == ExpressionKind::UnaryPlus)
		{
		}
		else if (node->kind == ExpressionKind::UnaryMinus)
		{
			byteCode.push_back(minus_float);
		}
		else
		{
			throw wstring(L"wrong unary operation, where operand is float");
		}
	}
	else if (node->type.IsDouble())
	{
		if (node->kind == ExpressionKind::UnaryPlus)
		{
		}
		else if (node->kind == ExpressionKind::UnaryMinus)
		{
			byteCode.push_back(minus_double);
		}
		else
		{
			throw wstring(L"wrong unary operation, where operand is double");
		}
	}
	else if (node->type.IsBoolean() && node->kind == ExpressionKind::Not)
	{
		byteCode.push_back(logical_not);
	}
	else
	{
		throw wstring(L"wrong unary operation");
	}
}
void Compiler::Visit(BinaryExpression* node)
{
	node->left->Accept(this);
	node->right->Accept(this);
	if (node->left->type.IsInt() && node->right->type.IsInt())
	{
		if (node->kind == ExpressionKind::Add)
		{
			byteCode.push_back(add_int);
		}
		else if (node->kind == ExpressionKind::Subtract)
		{
			byteCode.push_back(sub_int);
		}
		else if (node->kind == ExpressionKind::Multiply)
		{
			byteCode.push_back(mul_int);
		}
		else if (node->kind == ExpressionKind::Divide)
		{
			byteCode.push_back(div_int);
		}
		else if (node->kind == ExpressionKind::Modulo)
		{
			byteCode.push_back(mod_int);
		}
		else if (node->kind == ExpressionKind::GreaterThan)
		{
			byteCode.push_back(gt_int);
		}
		else if (node->kind == ExpressionKind::LessThan)
		{
			byteCode.push_back(lt_int);
		}
		else if (node->kind == ExpressionKind::GreaterThanOrEqual)
		{
			byteCode.push_back(ge_int);
		}
		else if (node->kind == ExpressionKind::LessThanOrEqual)
		{
			byteCode.push_back(le_int);
		}
		else if (node->kind == ExpressionKind::Equal)
		{
			byteCode.push_back(eq_int);
		}
		else if (node->kind == ExpressionKind::NotEqual)
		{
			byteCode.push_back(ne_int);
		}
		else
		{
			throw wstring(L"wrong binary operation for int");
		}
	}
	else if (node->left->type.IsLong() && node->right->type.IsLong())
	{
		if (node->kind == ExpressionKind::Add)
		{
			byteCode.push_back(add_long);
		}
		else if (node->kind == ExpressionKind::Subtract)
		{
			byteCode.push_back(sub_long);
		}
		else if (node->kind == ExpressionKind::Multiply)
		{
			byteCode.push_back(mul_long);
		}
		else if (node->kind == ExpressionKind::Divide)
		{
			byteCode.push_back(div_long);
		}
		else if (node->kind == ExpressionKind::Modulo)
		{
			byteCode.push_back(mod_long);
		}
		else if (node->kind == ExpressionKind::GreaterThan)
		{
			byteCode.push_back(gt_long);
		}
		else if (node->kind == ExpressionKind::LessThan)
		{
			byteCode.push_back(lt_long);
		}
		else if (node->kind == ExpressionKind::GreaterThanOrEqual)
		{
			byteCode.push_back(ge_long);
		}
		else if (node->kind == ExpressionKind::LessThanOrEqual)
		{
			byteCode.push_back(le_long);
		}
		else if (node->kind == ExpressionKind::Equal)
		{
			byteCode.push_back(eq_long);
		}
		else if (node->kind == ExpressionKind::NotEqual)
		{
			byteCode.push_back(ne_long);
		}
		else
		{
			throw wstring(L"wrong binary operation for long");
		}
	}
	else if (node->left->type.IsFloat() && node->right->type.IsFloat())
	{
		if (node->kind == ExpressionKind::Add)
		{
			byteCode.push_back(add_float);
		}
		else if (node->kind == ExpressionKind::Subtract)
		{
			byteCode.push_back(sub_float);
		}
		else if (node->kind == ExpressionKind::Multiply)
		{
			byteCode.push_back(mul_float);
		}
		else if (node->kind == ExpressionKind::Divide)
		{
			byteCode.push_back(div_float);
		}
		else if (node->kind == ExpressionKind::GreaterThan)
		{
			byteCode.push_back(gt_float);
		}
		else if (node->kind == ExpressionKind::LessThan)
		{
			byteCode.push_back(lt_float);
		}
		else if (node->kind == ExpressionKind::GreaterThanOrEqual)
		{
			byteCode.push_back(ge_float);
		}
		else if (node->kind == ExpressionKind::LessThanOrEqual)
		{
			byteCode.push_back(le_float);
		}
		else if (node->kind == ExpressionKind::Equal)
		{
			byteCode.push_back(eq_float);
		}
		else if (node->kind == ExpressionKind::NotEqual)
		{
			byteCode.push_back(ne_float);
		}
		else
		{
			throw wstring(L"wrong binary operation for float");
		}
	}
	else if (node->left->type.IsDouble() && node->right->type.IsDouble())
	{
		if (node->kind == ExpressionKind::Add)
		{
			byteCode.push_back(add_double);
		}
		else if (node->kind == ExpressionKind::Subtract)
		{
			byteCode.push_back(sub_double);
		}
		else if (node->kind == ExpressionKind::Multiply)
		{
			byteCode.push_back(mul_double);
		}
		else if (node->kind == ExpressionKind::Divide)
		{
			byteCode.push_back(div_double);
		}
		else if (node->kind == ExpressionKind::GreaterThan)
		{
			byteCode.push_back(gt_double);
		}
		else if (node->kind == ExpressionKind::LessThan)
		{
			byteCode.push_back(lt_double);
		}
		else if (node->kind == ExpressionKind::GreaterThanOrEqual)
		{
			byteCode.push_back(ge_double);
		}
		else if (node->kind == ExpressionKind::LessThanOrEqual)
		{
			byteCode.push_back(le_double);
		}
		else if (node->kind == ExpressionKind::Equal)
		{
			byteCode.push_back(eq_double);
		}
		else if (node->kind == ExpressionKind::NotEqual)
		{
			byteCode.push_back(ne_double);
		}
		else
		{
			throw wstring(L"wrong binary operation for double");
		}
	}
	else if (node->left->type.IsBoolean() && node->right->type.IsBoolean())
	{
		if (node->kind == ExpressionKind::And)
		{
			byteCode.push_back(logical_and);
		}
		else if (node->kind == ExpressionKind::Or)
		{
			byteCode.push_back(logical_or);
		}
		else if (node->kind == ExpressionKind::Equal)
		{
			byteCode.push_back(eq_int);
		}
		else if (node->kind == ExpressionKind::NotEqual)
		{
			byteCode.push_back(ne_int);
		}
		else
		{
			throw wstring(L"wrong binary operation for boolean");
		}
	}
	else
	{
		throw wstring(L"not supported type");
	}
}
void Compiler::Visit(AssignExpression* node)
{
	node->value->Accept(this);
	if (node->type.IsInt())
	{
		if (node->location.IsLocal())
		{
			// local variable
			byteCode.push_back(pop_local_int);
			byteCode.push_back(node->location.offset);
		}
		else
		{
			byteCode.push_back(pop_field_int);
			constantPool.push_back(constant_int);
			ConvertInt(constantPool, node->location.index);
			byteCode.push_back(constantsCount);
			constantsCount++;
			byteCode.push_back(node->location.offset);
		}
	}
	else if (node->type.IsLong())
	{
		// To DO
	}
}
void Compiler::Visit(BlockExpression* node)
{
	for (auto& e : node->expressions)
	{
		e->Accept(this);
	}
}
void Compiler::Visit(IfThenExpression* node)
{
	node->condition->Accept(this);
	byteCode.push_back(jump_if_false);
	int32_t index = byteCode.size();
	ConvertUShort(byteCode, 0);
	node->ifTrue->Accept(this);
	int32_t target = byteCode.size();
	byteCode.at(index) = target % 256;
	byteCode.at(index + 1) = target / 256;
}
void Compiler::Visit(IfThenElseExpression* node)
{
	node->condition->Accept(this);
	byteCode.push_back(jump_if_false);
	int32_t index1 = byteCode.size();
	ConvertUShort(byteCode, 0);

	node->ifTrue->Accept(this);
	byteCode.push_back(jump);
	int32_t index2 = byteCode.size();
	ConvertUShort(byteCode, 0);

	int32_t target = byteCode.size();
	byteCode.at(index1) = target % 256;
	byteCode.at(index1 + 1) = target / 256;
	node->ifFalse->Accept(this);
	int32_t target2 = byteCode.size();
	byteCode.at(index2) = target2 % 256;
	byteCode.at(index2 + 1) = target / 256;
}
void Compiler::Visit(CallExpression* node)
{
	for (auto& arg : node->arguments)
	{
		arg->Accept(this);
	}
	node->function->Accept(this);
	byteCode.push_back(invoke);
}
void Compiler::Visit(VariableExpression* node)
{
	if (node->location.IsLocal())
	{
		if (node->type.IsInt())
		{
			byteCode.push_back(push_local_int);
			byteCode.push_back(node->location.offset);
		}
		else if (node->type.IsLong())
		{
			byteCode.push_back(push_local_long);
			byteCode.push_back(node->location.offset);
		}
		else if (node->type.IsFloat())
		{
			byteCode.push_back(push_local_float);
			byteCode.push_back(node->location.offset);
		}
		else if (node->type.IsDouble())
		{
			byteCode.push_back(push_local_int);
			byteCode.push_back(node->location.offset);
		}
		else
		{
			throw NotImplementedException();
		}
	}
	else
	{
		if (node->type.IsFunction())
		{
			byteCode.push_back(push_function);
			constantPool.push_back(constant_int);
			ConvertInt(constantPool, node->location.index);
			byteCode.push_back(constantsCount);
			constantsCount++;
			byteCode.push_back(node->location.offset);
		}
		else
		{
			throw NotImplementedException();
		}
	}
}
void Compiler::Visit(ReturnExpression* node)
{
	node->value->Accept(this);
	if (node->type.IsInt())
	{
		byteCode.push_back(return_int);
	}
	else if (node->type.IsLong())
	{
		byteCode.push_back(return_long);
	}
	else if (node->type.IsFloat())
	{
		byteCode.push_back(return_float);
	}
	else if (node->type.IsDouble())
	{
		byteCode.push_back(return_double);
	}
	else
	{
		throw wstring(L"not supported return type");
	}
}
void Compiler::Visit(WhileExpression* node)
{
}
void Compiler::Visit(DotExpression* node)
{
	Type& objType = node->object->type;
	if (objType.IsModule())
	{
		if (node->value.type() == typeid(Function))
		{
			Function f = any_cast<Function>(node->value);
			byteCode.push_back(push_function);
			constantPool.push_back(constant_int);
			ConvertInt(constantPool, f.location.index);
			byteCode.push_back(constantsCount);
			constantsCount++;
			byteCode.push_back(f.location.offset);
		}
		else
		{
			throw NotImplementedException();
		}
	}
	else
	{
		throw NotImplementedException();
	}
}
CompiledModule::CompiledModule()
{
}
CompiledModule::CompiledModule(int32_t index, int32_t fieldCount,
							   vector<CompiledFunction> functions)
	: index{index}
	, fieldCount{fieldCount}
	, functions{functions}
{
}
ByteCode CompiledModule::EmitByteCode()
{
	ByteCode code;
	ConvertInt(code, index);
	code.push_back(fieldCount);
	code.push_back(functions.size());
	for (auto& function : functions)
	{
		for (auto b : function.EmitByteCode())
		{
			code.push_back(b);
		}
	}
	return code;
}
CompiledClass::CompiledClass()
{
}
CompiledClass::CompiledClass(int32_t index, int32_t fieldCount,
							 vector<CompiledFunction> methods)
	: index{index}
	, fieldCount{fieldCount}
	, methods{methods}
{
}
ByteCode CompiledClass::EmitByteCode()
{
	ByteCode code;
	code.push_back(index);
	code.push_back(fieldCount);
	code.push_back(methods.size());
	for (auto& method : methods)
	{
		for (auto b : method.EmitByteCode())
		{
			code.push_back(b);
		}
	}
	return code;
}
CompiledFunction::CompiledFunction()
{
}
CompiledFunction::CompiledFunction(wstring name, int32_t index,
								   int32_t stackSize, int32_t argsCount,
								   int32_t localsCount, int32_t constantCount,
								   ByteCode constantPool, ByteCode byteCode)
	: name{name}
	, index{index}
	, stackSize{stackSize}
	, argsCount{argsCount}
	, localsCount{localsCount}
	, constantCount{constantCount}
	, constantPool{constantPool}
	, byteCode{byteCode}
{
}
ByteCode CompiledFunction::EmitByteCode()
{
	ByteCode code;
	code.push_back(index);
	ConvertInt(code, stackSize);
	code.push_back(argsCount);
	code.push_back(localsCount);
	code.push_back(constantCount);
	ConvertUShort(code, byteCode.size());
	for (auto& b : constantPool)
	{
		code.push_back(b);
	}
	for (auto& b : byteCode)
	{
		code.push_back(b);
	}
	return code;
}
CompiledProgram::CompiledProgram()
{
}
CompiledProgram::CompiledProgram(vector<CompiledModule> modules,
								 vector<CompiledClass> classes)
	: modules{modules}
	, classes{classes}
{
}
void CompiledProgram::SearchMainFunction()
{
	for (auto& moduleInfo : modules)
	{
		for (auto& f : moduleInfo.functions)
		{
			if (f.name == L"Main")
			{
				mainModule = moduleInfo.index;
				mainFunction = f.index;
				return;
			}
		}
	}
	mainModule = -1;
	mainFunction = -1;
	throw wstring(L"missing main function");
}
ByteCode CompiledProgram::EmitByteCode()
{
	SearchMainFunction();
	ByteCode code;
	ConvertInt(code, mainModule);
	code.push_back(mainFunction);
	for (auto& module : modules)
	{
		code.push_back(0);
		for (auto b : module.EmitByteCode())
		{
			code.push_back(b);
		}
	}
	for (auto& _class : classes)
	{
		code.push_back(1);
		for (auto b : _class.EmitByteCode())
		{
			code.push_back(b);
		}
	}
	return code;
}
void ConvertValue(ByteCode& byteCode, byte* bytes, int32_t length)
{
	for (int32_t i = 0; i < length; i++)
	{
		byteCode.push_back(bytes[i]);
	}
}
void ConvertUShort(ByteCode& byteCode, uint16_t value)
{
	ConvertValue(byteCode, (byte*) &value, sizeof(uint16_t));
}
void ConvertInt(ByteCode& byteCode, int32_t value)
{
	ConvertValue(byteCode, (byte*) &value, sizeof(int32_t));
}
void ConvertLong(ByteCode& byteCode, int64_t value)
{
	ConvertValue(byteCode, (byte*) &value, sizeof(int64_t));
}
void ConvertFloat(ByteCode& byteCode, float value)
{
	ConvertValue(byteCode, (byte*) &value, sizeof(float));
}
void ConvertDouble(ByteCode& byteCode, double value)
{
	ConvertValue(byteCode, (byte*) &value, sizeof(double));
}
void ConvertString(ByteCode& byteCode, wstring text)
{
	int32_t length = text.size();
	ConvertInt(byteCode, length);
	for (int32_t i = 0; i < length; i++)
	{
		int32_t character = text[i];
		ConvertInt(byteCode, character);
	}
}