#include "TestLexer.hpp"
#include "TestParser.hpp"
#include "TestType.hpp"
#include "TestTypeChecker.hpp"
#include <iostream>
#include <string>
using std::endl;
using std::wcout;
int main()
{
	std::locale::global(std::locale(""));
	TestNumber();
	TestHelloWorld();
	TestSimpleArithmetic();
	TestAddition();
	TestFactorial();
	TestBasicTypes();
	TestMultiplication();

	TestTypeChecker::TestMultiplication();
	TestTypeChecker::TestCircleArea();
	TestTypeChecker::TestSummation();
	return 0;
}
