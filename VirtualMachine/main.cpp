#include "Test.hpp"
#include <iostream>
int main()
{
	std::locale::global(std::locale(""));
	TestMax();
	return 0;
}