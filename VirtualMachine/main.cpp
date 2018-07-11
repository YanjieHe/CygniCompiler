#include "Test.hpp"
#include <iostream>
int main()
{
	std::locale::global(std::locale(""));
	// TestFactorial();
	// TestFibonacci();
	// TestFactorialAndFibonacci();
	TestSummation();
	return 0;
}