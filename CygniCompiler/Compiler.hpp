#ifndef COMPILER_HPP
#define COMPILER_HPP
#include "Expression.hpp"
#include "Namespace.hpp"
typedef unsigned char byte;
typedef vector<byte> ByteCode;
class CompiledModule;
class CompiledClass;
class CompiledFunction;
class CompiledProgram;
class Compiler : Expression::Visitor
{
public:
	int32_t constantsCount;
	ByteCode constantPool;
	ByteCode byteCode;
	vector<CompiledModule> modules;
	vector<CompiledClass> classes;
	Compiler();
	CompiledProgram Compile(NamespaceRecord& nsRecord);
	void CompileNamespace(shared_ptr<Namespace>& nsPtr);
	CompiledFunction CompileFunction(Function& function);

	void Visit(ConstantExpression* node) override;
	void Visit(UnaryExpression* node) override;
	void Visit(BinaryExpression* node) override;
	void Visit(AssignExpression* node) override;
	void Visit(BlockExpression* node) override;
	void Visit(IfThenExpression* node) override;
	void Visit(IfThenElseExpression* node) override;
	void Visit(CallExpression* node) override;
	void Visit(VariableExpression* node) override;
	void Visit(ReturnExpression* node) override;
	void Visit(WhileExpression* node) override;
	void Visit(DotExpression* node) override;
};

class CompiledModule
{
public:
	int32_t index;
	int32_t fieldCount;
	vector<CompiledFunction> functions;

	CompiledModule();
	CompiledModule(int32_t index, int32_t fieldCount,
				   vector<CompiledFunction> functions);
	ByteCode EmitByteCode();
};
class CompiledClass
{
public:
	int32_t index;
	int32_t fieldCount;
	vector<CompiledFunction> methods;

	CompiledClass();
	CompiledClass(int32_t index, int32_t fieldCount,
				  vector<CompiledFunction> methods);
	ByteCode EmitByteCode();
};
class CompiledFunction
{
public:
	int32_t index;
	int32_t stackSize;
	int32_t argsCount;
	int32_t localsCount;

	int32_t constantCount;
	ByteCode constantPool;
	ByteCode byteCode;

	CompiledFunction();
	CompiledFunction(int32_t index, int32_t stackSize, int32_t argsCount,
					 int32_t localsCount, int32_t constantCount,
					 ByteCode constantPool, ByteCode byteCode);
	ByteCode EmitByteCode();
};
class CompiledProgram
{
public:
	vector<CompiledModule> modules;
	vector<CompiledClass> classes;

	CompiledProgram();
	CompiledProgram(vector<CompiledModule> modules,
					vector<CompiledClass> classes);
	ByteCode EmitByteCode();
};

void ConvertValue(ByteCode& byteCode, byte* bytes, int32_t length);
void ConvertUShort(ByteCode& byteCode, uint16_t value);
void ConvertInt(ByteCode& byteCode, int32_t value);
void ConvertLong(ByteCode& byteCode, int64_t value);
void ConvertFloat(ByteCode& byteCode, float value);
void ConvertDouble(ByteCode& byteCode, double value);
void ConvertString(ByteCode& byteCode, wstring text);
#endif // COMPILER_HPP