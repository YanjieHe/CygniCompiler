#include "Test.hpp"
#include "ByteCodeViewer.hpp"
void TestReadAndWriteBinaryFile()
{
	ByteCode code = vector<byte>{1, 2, 3, 4, 5};
	WriteBytes("./binaries/test_binary_code.bin", code);
	ByteCode input = ReadBytes("./binaries/test_binary_code.bin");
	if (code == input)
	{
		wcout << __func__ << L" passed" << endl;
	}
	else
	{
		wcout << __func__ << L" failed" << endl;
	}
}
void TestFactorialAndFibonacci()
{
	ByteCode code = ReadBytes(
		"test_cases/FactorialAndFibonacci/factorial_and_fibonacci.bin");

	ByteCodeViewer viewer(code);
	viewer.View();
}