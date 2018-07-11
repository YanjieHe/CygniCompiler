#include "Test.hpp"
#include <iostream>
int main()
{
	std::locale::global(std::locale(""));
	// TestFactorial();
	// TestFibonacci();
	TestFactorialAndFibonacci();
	return 0;
}