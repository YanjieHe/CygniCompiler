#ifndef COMPILER_HPP
#define COMPILER_HPP
#include "Expression.hpp"
#include "Namespace.hpp"
typedef unsigned char byte;
typedef vector<byte> ByteCode;
class CompiledModule;
class CompiledClass;
class CompiledFunction;
class CompiledNativeFunction;
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
	CompiledNativeFunction
		CompileNativeFunction(NativeFunction& nativeFunction);

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
	vector<CompiledNativeFunction> nativeFunctions;

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
	wstring name;
	int32_t index;
	int32_t stackSize;
	int32_t argsCount;
	int32_t localsCount;

	int32_t constantCount;
	ByteCode constantPool;
	ByteCode byteCode;

	CompiledFunction();
	CompiledFunction(wstring name, int32_t index, int32_t stackSize,
					 int32_t argsCount, int32_t localsCount,
					 int32_t constantCount, ByteCode constantPool,
					 ByteCode byteCode);
	ByteCode EmitByteCode();
};
class CompiledNativeFunction
{
public:
	wstring libraryPath;
	wstring functionName;
	int32_t index;
	int32_t argsCount;
	CompiledNativeFunction();
	CompiledNativeFunction(wstring libraryPath, wstring functionName,
						   int32_t index, int32_t argsCount);
	ByteCode EmitByteCode();
};
class CompiledProgram
{
public:
	vector<CompiledModule> modules;
	vector<CompiledClass> classes;
	int32_t mainModule;
	int32_t mainFunction;
	CompiledProgram();
	CompiledProgram(vector<CompiledModule> modules,
					vector<CompiledClass> classes);
	void SearchMainFunction();
	ByteCode EmitByteCode();
};

#endif // COMPILER_HPP