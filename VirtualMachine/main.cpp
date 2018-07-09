#include "VM.hpp"
#include <iostream>
int main()
{
	std::locale::global(std::locale(""));
	VM vm;
	vector<byte> code = {0, 0,  0, 0,  0,  0,  1, 0,  0, 0,  0, 0,  0,  2,
						 2, 14, 0, 0,  10, 0,  0, 0,  0, 20, 0, 0,  0,  62,
						 0, 73, 0, 62, 1,  73, 1, 67, 0, 67, 1, 12, 103};
	ByteCodeReader reader(code);
	vm.Load(reader);
	vm.Run();
}