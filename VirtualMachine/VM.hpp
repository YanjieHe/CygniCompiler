#ifndef VM_HPP
#define VM_HPP
#include "ByteCodeReader.hpp"
#include "Value.hpp"
#define MAX_STACK_SIZE 100000
class VM
{
public:
	vector<Module> modules;
	vector<Class> classes;

	Function main;

	vector<Value> stack;
	int32_t sp = -1;
	Function* function;
	ByteCode* code;
	ConstantPool* constantPool;

	VM();
	void Load(ByteCodeReader& reader);
	Module LoadModule(ByteCodeReader& reader);
	Function LoadFunction(ByteCodeReader& reader);
	ConstantPool LoadConstantPool(ByteCodeReader& reader,
								  int32_t constantCount);
	void Run();
};

inline int32_t GetUShort(ByteCode* code, int32_t pc)
{
	return ((*code)[pc + 1]) + ((*code)[pc + 2] << 8);
}
void ShowStack(vector<Value>& stack);
#endif // VM_HPP