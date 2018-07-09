#include "Test.hpp"
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