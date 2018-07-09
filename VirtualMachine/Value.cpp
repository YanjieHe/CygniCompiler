#include "Value.hpp"
Object::Object()
{
}
Object::~Object()
{
}
String::String()
{
}
String::~String()
{
}
String::String(wstring text)
	: text{text}
{
}
Module::Module()
{
}
Module::Module(int32_t index, int32_t fieldCount, vector<Function> functions)
	: index{index}
	, fieldCount{fieldCount}
	, functions{functions}
{
}
Function::Function()
{
}
Function::~Function()
{
}
Function::Function(int32_t index, int32_t stackSize, int32_t args,
				   int32_t locals, ConstantPool constants, ByteCode code)
	: index{index}
	, stackSize{stackSize}
	, args{args}
	, locals{locals}
	, constants{constants}
	, code{code}
{
}