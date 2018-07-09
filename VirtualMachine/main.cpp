#include "Test.hpp"
#include <iostream>
int main()
{
	std::locale::global(std::locale(""));
	TestFactorial();
	return 0;
}