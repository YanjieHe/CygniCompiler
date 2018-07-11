#include "VM.hpp"
#include "Instruction.hpp"
#include <iostream>
using std::endl;
using std::wcout;
VM::VM()
	: stack(MAX_STACK_SIZE)
{
}
void VM::Load(ByteCodeReader& reader)
{
	modules.clear();
	classes.clear();
	int32_t mainModule = reader.ReadInt();
	int32_t mainFunction = reader.Read();
	while (!reader.IsEof())
	{
		int32_t b = reader.Read();
		if (b == 0)
		{
			modules.push_back(LoadModule(reader));
		}
		else if (b == 1)
		{
			throw wstring(L"error1");
		}
		else
		{
			throw wstring(L"error2");
		}
	}
	main = modules.at(mainModule).functions.at(mainFunction);
	code = &(main.code);
	constantPool = &(main.constants);
}
Module VM::LoadModule(ByteCodeReader& reader)
{
	int32_t index = reader.ReadInt();
	int32_t fieldCount = reader.Read();
	int32_t functionCount = reader.Read();
	wcout << L"module index = " << index << endl;
	wcout << L"field count = " << fieldCount << endl;
	wcout << L"function count = " << functionCount << endl;
	vector<Function> functions;
	functions.reserve(functionCount);
	for (int32_t i = 0; i < functionCount; i++)
	{
		functions.push_back(LoadFunction(reader));
	}
	return Module(index, fieldCount, functions);
}
Function VM::LoadFunction(ByteCodeReader& reader)
{
	int32_t index = reader.Read();
	int32_t stackSize = reader.ReadInt();
	int32_t args = reader.Read();
	int32_t locals = reader.Read();
	int32_t constantCount = reader.Read();
	int32_t functionCodeLength = reader.ReadUShort();
	wcout << L"index = " << index << endl;
	wcout << L"stack size = " << stackSize << endl;
	wcout << L"args = " << args << endl;
	wcout << L"locals = " << locals << endl;
	wcout << L"constant count = " << constantCount << endl;
	wcout << L"function code length = " << functionCodeLength << endl;
	ConstantPool pool = LoadConstantPool(reader, constantCount);
	ByteCode functionCode;
	functionCode.reserve(functionCodeLength);
	for (int32_t i = 0; i < functionCodeLength; i++)
	{
		functionCode.push_back(reader.Read());
	}
	return Function(index, stackSize, args, locals, pool, functionCode);
}
ConstantPool VM::LoadConstantPool(ByteCodeReader& reader, int32_t constantCount)
{
	ConstantPool pool;
	for (int32_t i = 0; i < constantCount; i++)
	{
		int32_t b = reader.Read();
		Value value;
		switch (b)
		{
		case constant_int:
		{
			value.int_v = reader.ReadInt();
			pool.push_back(value);
			break;
		}
		case constant_long:
		{
			value.long_v = reader.ReadLong();
			pool.push_back(value);
			break;
		}
		case constant_float:
		{
			value.float_v = reader.ReadFloat();
			pool.push_back(value);
			break;
		}
		case constant_double:
		{
			value.double_v = reader.ReadDouble();
			pool.push_back(value);
			break;
		}
		default:
			throw wstring(L"not supported constant");
		}
	}
	return pool;
}
void VM::Run()
{
	wcout << endl;
	wcout << L"**************** start vm ****************" << endl;
	wcout << endl;

	int32_t pc = 0;
	int32_t fp = 0;
	code = &(main.code);
	sp = sp + main.args + main.locals;
	sp++;
	stack[sp].int_v = 0;
	sp++;
	stack[sp].object = nullptr;
	sp++;
	stack[sp].int_v = 0;

	function = &(main);

	int32_t codeLength = code->size();
	while (pc < codeLength)
	{
		int32_t opcode = (*code)[pc];
		switch (opcode)
		{
		case push_constant_int:
		{
			int32_t index = (*code)[pc + 1];
			sp++;
			stack[sp].int_v = (*constantPool)[index].int_v;
			pc += 2;
			break;
		}
		case push_constant_long:
		{
			int32_t index = (*code)[pc + 1];
			sp++;
			stack[sp].long_v = (*constantPool)[index].long_v;
			pc += 2;
			break;
		}
		case push_constant_float:
		{
			int32_t index = (*code)[pc + 1];
			sp++;
			stack[sp].float_v = (*constantPool)[index].float_v;
			pc += 2;
			break;
		}
		case push_constant_double:
		{
			int32_t index = (*code)[pc + 1];
			sp++;
			stack[sp].double_v = (*constantPool)[index].double_v;
			pc += 2;
			break;
		}
		case push_constant_string:
		{
			int32_t index = (*code)[pc + 1];
			sp++;
			stack[sp].object = (*constantPool)[index].object;
			pc += 2;
			break;
		}
		case push_local_int:
		{
			int32_t index = (*code)[pc + 1];
			sp++;
			stack[sp].int_v = stack[fp + index].int_v;
			// wcout << L"push local int = " << stack[sp].int_v << endl;
			pc += 2;
			break;
		}
		case push_local_long:
		{
			int32_t index = (*code)[pc + 1];
			sp++;
			stack[sp].long_v = stack[fp + index].long_v;
			pc += 2;
			break;
		}
		case push_local_float:
		{
			int32_t index = (*code)[pc + 1];
			sp++;
			stack[sp].float_v = stack[fp + index].float_v;
			pc += 2;
			break;
		}
		case push_local_double:
		{
			int32_t index = (*code)[pc + 1];
			sp++;
			stack[sp].double_v = stack[fp + index].double_v;
			pc += 2;
			break;
		}
		case push_local_object:
		{
			int32_t index = (*code)[pc + 1];
			sp++;
			stack[sp].object = stack[fp + index].object;
			pc += 2;
			break;
		}
		case pop_local_int:
		{
			int32_t index = (*code)[pc + 1];
			stack[fp + index].int_v = stack[sp].int_v;
			sp--;
			pc += 2;
			break;
		}
		case pop_local_long:
		{
			int32_t index = (*code)[pc + 1];
			stack[fp + index].long_v = stack[sp].long_v;
			sp--;
			pc += 2;
			break;
		}
		case pop_local_float:
		{
			int32_t index = (*code)[pc + 1];
			stack[fp + index].float_v = stack[sp].float_v;
			sp--;
			pc += 2;
			break;
		}
		case pop_local_double:
		{
			int32_t index = (*code)[pc + 1];
			stack[fp + index].double_v = stack[sp].double_v;
			sp--;
			pc += 2;
			break;
		}
		case pop_local_object:
		{
			int32_t index = (*code)[pc + 1];
			stack[fp + index].object = stack[sp].object;
			sp--;
			pc += 2;
			break;
		}
		case add_int:
		{
			stack[sp - 1].int_v = stack[sp - 1].int_v + stack[sp].int_v;
			sp--;
			pc++;
			break;
		}
		case sub_int:
		{
			stack[sp - 1].int_v = stack[sp - 1].int_v - stack[sp].int_v;
			sp--;
			pc++;
			break;
		}
		case mul_int:
		{
			stack[sp - 1].int_v = stack[sp - 1].int_v * stack[sp].int_v;
			sp--;
			pc++;
			break;
		}
		case div_int:
		{
			stack[sp - 1].int_v = stack[sp - 1].int_v / stack[sp].int_v;
			sp--;
			pc++;
			break;
		}
		case mod_int:
		{
			stack[sp - 1].int_v = stack[sp - 1].int_v % stack[sp].int_v;
			sp--;
			pc++;
			break;
		}
		case gt_int:
		{
			stack[sp - 1].int_v = stack[sp - 1].int_v > stack[sp].int_v;
			sp--;
			pc++;
			break;
		}
		case lt_int:
		{
			stack[sp - 1].int_v = stack[sp - 1].int_v < stack[sp].int_v;
			sp--;
			pc++;
			break;
		}
		case ge_int:
		{
			stack[sp - 1].int_v = stack[sp - 1].int_v >= stack[sp].int_v;
			sp--;
			pc++;
			break;
		}
		case le_int:
		{
			stack[sp - 1].int_v = stack[sp - 1].int_v <= stack[sp].int_v;
			sp--;
			pc++;
			break;
		}
		case eq_int:
		{
			stack[sp - 1].int_v = stack[sp - 1].int_v == stack[sp].int_v;
			sp--;
			pc++;
			break;
		}
		case ne_int:
		{
			stack[sp - 1].int_v = stack[sp - 1].int_v != stack[sp].int_v;
			sp--;
			pc++;
			break;
		}
		case add_long:
		{
			stack[sp - 1].long_v = stack[sp - 1].long_v + stack[sp].long_v;
			sp--;
			pc++;
			break;
		}
		case sub_long:
		{
			stack[sp - 1].long_v = stack[sp - 1].long_v - stack[sp].long_v;
			sp--;
			pc++;
			break;
		}
		case mul_long:
		{
			stack[sp - 1].long_v = stack[sp - 1].long_v * stack[sp].long_v;
			sp--;
			pc++;
			break;
		}
		case div_long:
		{
			stack[sp - 1].long_v = stack[sp - 1].long_v / stack[sp].long_v;
			sp--;
			pc++;
			break;
		}
		case mod_long:
		{
			stack[sp - 1].long_v = stack[sp - 1].long_v % stack[sp].long_v;
			sp--;
			pc++;
			break;
		}
		case gt_long:
		{
			stack[sp - 1].long_v = stack[sp - 1].long_v > stack[sp].long_v;
			sp--;
			pc++;
			break;
		}
		case lt_long:
		{
			stack[sp - 1].long_v = stack[sp - 1].long_v < stack[sp].long_v;
			sp--;
			pc++;
			break;
		}
		case ge_long:
		{
			stack[sp - 1].long_v = stack[sp - 1].long_v >= stack[sp].long_v;
			sp--;
			pc++;
			break;
		}
		case le_long:
		{
			stack[sp - 1].long_v = stack[sp - 1].long_v <= stack[sp].long_v;
			sp--;
			pc++;
			break;
		}
		case eq_long:
		{
			stack[sp - 1].long_v = stack[sp - 1].long_v == stack[sp].long_v;
			sp--;
			pc++;
			break;
		}
		case ne_long:
		{
			stack[sp - 1].long_v = stack[sp - 1].long_v != stack[sp].long_v;
			sp--;
			pc++;
			break;
		}
		case add_float:
		{
			stack[sp - 1].float_v = stack[sp - 1].float_v + stack[sp].float_v;
			sp--;
			pc++;
			break;
		}
		case sub_float:
		{
			stack[sp - 1].float_v = stack[sp - 1].float_v - stack[sp].float_v;
			sp--;
			pc++;
			break;
		}
		case mul_float:
		{
			stack[sp - 1].float_v = stack[sp - 1].float_v * stack[sp].float_v;
			sp--;
			pc++;
			break;
		}
		case div_float:
		{
			stack[sp - 1].float_v = stack[sp - 1].float_v / stack[sp].float_v;
			sp--;
			pc++;
			break;
		}
		case gt_float:
		{
			stack[sp - 1].float_v = stack[sp - 1].float_v > stack[sp].float_v;
			sp--;
			pc++;
			break;
		}
		case lt_float:
		{
			stack[sp - 1].float_v = stack[sp - 1].float_v < stack[sp].float_v;
			sp--;
			pc++;
			break;
		}
		case ge_float:
		{
			stack[sp - 1].float_v = stack[sp - 1].float_v >= stack[sp].float_v;
			sp--;
			pc++;
			break;
		}
		case le_float:
		{
			stack[sp - 1].float_v = stack[sp - 1].float_v <= stack[sp].float_v;
			sp--;
			pc++;
			break;
		}
		case eq_float:
		{
			stack[sp - 1].float_v = stack[sp - 1].float_v == stack[sp].float_v;
			sp--;
			pc++;
			break;
		}
		case ne_float:
		{
			stack[sp - 1].float_v = stack[sp - 1].float_v != stack[sp].float_v;
			sp--;
			pc++;
			break;
		}
		case add_double:
		{
			stack[sp - 1].double_v =
				stack[sp - 1].double_v + stack[sp].double_v;
			sp--;
			pc++;
			break;
		}
		case sub_double:
		{
			stack[sp - 1].double_v =
				stack[sp - 1].double_v - stack[sp].double_v;
			sp--;
			pc++;
			break;
		}
		case mul_double:
		{
			stack[sp - 1].double_v =
				stack[sp - 1].double_v * stack[sp].double_v;
			sp--;
			pc++;
			break;
		}
		case div_double:
		{
			stack[sp - 1].double_v =
				stack[sp - 1].double_v / stack[sp].double_v;
			sp--;
			pc++;
			break;
		}
		case gt_double:
		{
			stack[sp - 1].double_v =
				stack[sp - 1].double_v > stack[sp].double_v;
			sp--;
			pc++;
			break;
		}
		case lt_double:
		{
			stack[sp - 1].double_v =
				stack[sp - 1].double_v < stack[sp].double_v;
			sp--;
			pc++;
			break;
		}
		case ge_double:
		{
			stack[sp - 1].double_v =
				stack[sp - 1].double_v >= stack[sp].double_v;
			sp--;
			pc++;
			break;
		}
		case le_double:
		{
			stack[sp - 1].double_v =
				stack[sp - 1].double_v <= stack[sp].double_v;
			sp--;
			pc++;
			break;
		}
		case eq_double:
		{
			stack[sp - 1].double_v =
				stack[sp - 1].double_v == stack[sp].double_v;
			sp--;
			pc++;
			break;
		}
		case ne_double:
		{
			stack[sp - 1].double_v =
				stack[sp - 1].double_v != stack[sp].double_v;
			sp--;
			pc++;
			break;
		}
		case return_int:
		{
			int32_t result = stack[sp].int_v;
			int32_t offset = fp + function->args + function->locals;
			pc = stack[offset].int_v;
			function = (Function*) stack[offset + 1].object;
			sp = fp;
			fp = stack[offset + 2].int_v;
			if (function)
			{
				code = &(function->code);
				codeLength = code->size();
				constantPool = &(function->constants);
				stack[sp].int_v = result;
				wcout << L"current result = " << result << endl;
				break;
			}
			else
			{
				wcout << L"result = " << result << endl;
				return;
			}
			break;
		}
		case invoke:
		{
			Function* f = (Function*) stack[sp].object;
			pc++;

			int32_t previousFunctionPointer = fp;
			fp = sp - (f->args);
			sp = fp + (f->args) + (f->locals);
			stack[sp].int_v = pc;
			sp++;
			stack[sp].object = function;
			sp++;
			stack[sp].int_v = previousFunctionPointer;
			sp++;

			function = f;
			code = &(function->code);
			codeLength = code->size();
			constantPool = &(function->constants);
			pc = 0;
			break;
		}
		case push_function:
		{
			int32_t cpIndex = (*code)[pc + 1];
			int32_t moduleIndex = constantPool->at(cpIndex).int_v;
			int32_t funIndex = (*code)[pc + 2];
			Function* f = &(modules.at(moduleIndex).functions.at(funIndex));
			pc += 3;
			sp++;
			stack[sp].object = f;
			//	wcout << L"store function at index " << sp << endl;
			break;
		}
		case jump_if_false:
		{
			int32_t target = GetUShort(code, pc);
			pc += 3;
			int32_t condition = stack[sp].int_v;
			sp--;
			if (!condition)
			{
				pc = target;
			}
			break;
		}
		case jump_if_true:
		{
			int32_t target = GetUShort(code, pc);
			pc += 3;
			int32_t condition = stack[sp].int_v;
			sp--;
			if (condition)
			{
				pc = target;
			}
			break;
		}
		case jump:
		{
			int32_t target = GetUShort(code, pc);
			// pc += 3; This is not necessary
			pc = target;
			break;
		}
		default:
		{
			wcout << L"not supported operation: " << opcode << endl;
			throw wstring(L"not supported operation");
		}
		}
	}
}
void ShowStack(vector<Value>& stack)
{
	for (int32_t i = 0; i < 100; i++)
	{
		wcout << i << L"(" << stack[i].int_v << L")" << L", ";
	}
	wcout << 100 << L"(" << stack[100].int_v << L")";
	wcout << endl;
}