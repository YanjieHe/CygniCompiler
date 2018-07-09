#include "Test.hpp"
#include "Instruction.hpp"
void TestAddition()
{
	VM vm;
	vector<byte> code = {0, 0,  0, 0,  0,  0,  1, 0,  0, 0,  0, 0,  0,  2,
						 2, 14, 0, 0,  10, 0,  0, 0,  0, 20, 0, 0,  0,  62,
						 0, 73, 0, 62, 1,  73, 1, 67, 0, 67, 1, 12, 103};
	ByteCodeReader reader(code);
	vm.Load(reader);
	vm.Run();
}
void TestMax()
{
	VM vm;
	vector<byte> code = {0,  0, 0,  0, 1,   0,  0,  0, 0,  0, 0,   2, 0,  0,
						 0,  0, 0,  2, 0,   0,  17, 0, 67, 0, 67,  1, 34, 5,
						 14, 0, 67, 0, 103, 3,  17, 0, 67, 1, 103, 1, 0,  0,
						 0,  0, 0,  2, 3,   17, 0,  0, 10, 0, 0,   0, 0,  20,
						 0,  0, 0,  0, 0,   0,  0,  0, 62, 0, 73,  0, 62, 1,
						 73, 1, 67, 0, 67,  1,  6,  2, 0,  8, 103};
	ByteCodeReader reader(code);
	vm.Load(reader);
	vm.Run();
}
void TestFactorial()
{
	VM vm;
	vector<byte> code = {0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 2,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 1,
						 2,
						 11,
						 0,
						 0,
						 10,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 62,
						 0,
						 6,
						 1,
						 1,
						 8,
						 73,
						 0,
						 push_local_int,
						 0,
						 103,
						 1,
						 0,
						 0,
						 0,
						 0,
						 1,
						 0,
						 4,
						 27,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 1,
						 0,
						 0,
						 0,
						 0,
						 1,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 0,
						 push_local_int,
						 0,
						 62,
						 0,
						 38,
						 5,
						 14,
						 0,
						 62,
						 1,
						 103,
						 jump,
						 27,
						 0,
						 push_local_int,
						 0,
						 push_local_int,
						 0,
						 push_constant_int,
						 2,
						 sub_int,
						 push_function,
						 3,
						 1,
						 invoke,
						 mul_int,
						 return_int};
	ByteCodeReader reader(code);
	vm.Load(reader);
	vm.Run();
}