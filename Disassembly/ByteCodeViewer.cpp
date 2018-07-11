#include "ByteCodeViewer.hpp"
#include "Instruction.hpp"
#include <iostream>
using std::endl;
using std::wcout;
ByteCodeViewer::ByteCodeViewer(ByteCode code)
	: code{code}
{
}
void ByteCodeViewer::View()
{
	ByteCodeReader reader(code);
	ViewHeader(reader);
	while (!reader.IsEof())
	{
		int32_t b = reader.Read();
		if (b == 0)
		{
			ViewModule(reader);
		}
		else
		{
			break;
		}
	}
}
void ByteCodeViewer::ViewHeader(ByteCodeReader& reader)
{
	mainModule = reader.ReadInt();
	mainFunction = reader.Read();
	wcout << L"main module = " << mainModule << endl;
	wcout << L"main function = " << mainFunction << endl;
}
void ByteCodeViewer::ViewModule(ByteCodeReader& reader)
{
	wcout << L"module:" << endl;
	int32_t moduleIndex = reader.ReadInt();
	int32_t fieldCount = reader.Read();
	int32_t functionCount = reader.Read();
	wcout << L"module index = " << moduleIndex << endl;
	wcout << L"field count = " << fieldCount << endl;
	wcout << L"function count = " << functionCount << endl;
	for (int32_t i = 0; i < functionCount; i++)
	{
		ViewFunction(reader);
	}
}
void ByteCodeViewer::ViewFunction(ByteCodeReader& reader)
{
	wcout << L"function:" << endl;
	int32_t index = reader.Read();
	int32_t stackSize = reader.ReadInt();
	int32_t argsCount = reader.Read();
	int32_t localsCount = reader.Read();
	int32_t constantCount = reader.Read();
	int32_t codeSize = reader.ReadUShort();
	wcout << L"index = " << index << endl;
	wcout << L"stack size = " << stackSize << endl;
	wcout << L"args = " << argsCount << endl;
	wcout << L"locals = " << localsCount << endl;
	wcout << L"constant count = " << constantCount << endl;
	wcout << L"code size = " << codeSize << endl;
	for (int32_t i = 0; i < constantCount; i++)
	{
		int32_t b = reader.Read();
		switch (b)
		{
		case constant_int:
		{
			wcout << L"constant int(" << i << L") = " << reader.ReadInt()
				  << endl;
			break;
		}
		case constant_long:
		{
			wcout << L"constant long(" << i << L") = " << reader.ReadLong()
				  << endl;
			break;
		}
		case constant_float:
		{
			wcout << L"constant float(" << i << L") = " << reader.ReadFloat()
				  << endl;
			break;
		}
		case constant_double:
		{
			wcout << L"constant double(" << i << L") = " << reader.ReadDouble()
				  << endl;
			break;
		}
		default:
		{
			throw wstring(L"not supported constant type");
		}
		}
	}
	ByteCode functionCode;
	for (int32_t i = 0; i < codeSize; i++)
	{
		functionCode.push_back(reader.Read());
	}
	ByteCodeReader functionCodeReader(functionCode);
	ViewCode(functionCodeReader);
}
void ByteCodeViewer::ViewCode(ByteCodeReader& reader)
{
	while (!reader.IsEof())
	{
		int32_t index = reader.index;
		int32_t instruction = reader.Read();
		wcout << L"    ";
		switch (instruction)
		{
		case add_int:
		case sub_int:
		case mul_int:
		case div_int:
		case mod_int:
		case add_long:
		case sub_long:
		case mul_long:
		case div_long:
		case mod_long:
		case add_float:
		case sub_float:
		case mul_float:
		case div_float:
		case add_double:
		case sub_double:
		case mul_double:
		case div_double:
		case gt_int:
		case lt_int:
		case ge_int:
		case le_int:
		case eq_int:
		case ne_int:
		case gt_long:
		case lt_long:
		case ge_long:
		case le_long:
		case eq_long:
		case ne_long:
		case gt_float:
		case lt_float:
		case ge_float:
		case le_float:
		case eq_float:
		case ne_float:
		case gt_double:
		case lt_double:
		case ge_double:
		case le_double:
		case eq_double:
		case ne_double:
		case eq_string:
		case ne_string:
		case eq_object:
		case ne_object:
		case return_int:
		case return_long:
		case return_float:
		case return_double:
		case return_string:
		case invoke:
		{
			wcout << index << L": " << InstructionToString(instruction) << endl;
			break;
		}
		case push_constant_int:
		case push_constant_long:
		case push_constant_float:
		case push_constant_double:
		case push_constant_string:
		{
			wcout << index << L": " << InstructionToString(instruction) << L" ";
			wcout << reader.Read() << endl;
			break;
		}
		case push_local_int:
		case push_local_long:
		case push_local_float:
		case push_local_double:
		case push_local_string:
		{
			wcout << index << L": " << InstructionToString(instruction) << L" ";
			wcout << reader.Read() << endl;
			break;
		}
		case pop_local_int:
		case pop_local_long:
		case pop_local_float:
		case pop_local_double:
		case pop_local_string:
		{
			wcout << index << L": " << InstructionToString(instruction) << L" ";
			wcout << reader.Read() << endl;
			break;
		}
		case jump:
		case jump_if_true:
		case jump_if_false:
		{
			wcout << index << L": " << InstructionToString(instruction) << L" ";
			wcout << reader.ReadUShort() << endl;
			break;
		}
		case push_function:
		{
			wcout << index << L": " << InstructionToString(instruction) << L" ";
			wcout << reader.Read() << L" ";
			wcout << reader.Read() << endl;
			break;
		}
		}
	}
}