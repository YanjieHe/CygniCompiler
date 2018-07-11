#ifndef VALUE_HPP
#define VALUE_HPP
#include <cstdint>
#include <string>
#include <vector>
using std::vector;
using std::wstring;
typedef unsigned char byte;
typedef vector<byte> ByteCode;
class Object
{
public:
	Object();
	virtual ~Object();
};

typedef union {
	int32_t int_v;
	int64_t long_v;
	float float_v;
	double double_v;
	Object* object;
} Value;

typedef vector<Value> ConstantPool;

class String : Object
{
public:
	wstring text;
	String();
	~String() override;
	String(wstring text);
};

class Function : public Object
{
public:
	int32_t index;
	int32_t stackSize;
	int32_t args;
	int32_t locals;
	ConstantPool constants;
	ByteCode code;
	Function();
	~Function() override;
	Function(int32_t index, int32_t stackSize, int32_t args, int32_t locals,
			 ConstantPool constants, ByteCode code);
};

class Method
{
public:
	int32_t classIndex;
	int32_t index;
	int32_t stackSize;
	int32_t argsCount;
	ConstantPool constants;
	ByteCode code;
};

class Module
{
public:
	int32_t index;
	int32_t fieldCount;
	vector<Function> functions;
	Function initializer;
	Module();
	Module(int32_t index, int32_t fieldCount, vector<Function> functions);
};

class Class
{
public:
	int32_t fieldCount;
	vector<Method> methods;
	vector<Method> constructors;
};

class IntArray : public Object
{
public:
	vector<int32_t> items;
	IntArray();
	~IntArray() override;
};

class ObjectArray : public Object
{
public:
	vector<Object*> items;
	ObjectArray();
	~ObjectArray() override;
};
#endif // VALUE_HPP