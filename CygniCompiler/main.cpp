#include "Test.hpp"
#include <iostream>
#include <string>
using std::endl;
using std::wcout;
int main()
{
	std::locale::global(std::locale(""));

	// TestLexer::TestNumber();
	// TestLexer::TestHelloWorld();

	// TestParser::TestSimpleArithmetic();
	// TestParser::TestAddition();
	// TestParser::TestFactorial();
	// TestParser::TestMultiplication();

	// TestType::TestBasicTypes();

	// TestTypeChecker::TestMultiplication();
	// TestTypeChecker::TestCircleArea();
	// TestTypeChecker::TestSummation();

	// TestCompiler::TestAddTwoNumbers();
	// TestCompiler::TestFactorial();
	// TestCompiler::TestFibonacci();
	TestCompiler::TestFactorialAndFibonacci();
	return 0;
}
