#ifndef TEST_HPP
#define TEST_HPP
#include "Lexer.hpp"
#include "Namespace.hpp"
#include <string>
#include <vector>
namespace TestLexer
{
using std::vector;
using std::wstring;
void AssertEqual(vector<Token>& x, vector<Token>& y, wstring message);
void ShowTokens(vector<Token>& tokens);
void ShowErrors(vector<LexicalException>& errors);
void TestNumber();
void TestHelloWorld();
}; // namespace TestLexer

namespace TestParser
{
void ShowSyntaxError(SyntaxException& ex);
void ViewNamespaceRecord(NamespaceRecord& nsRecord);
void TestSimpleArithmetic();
void TestAddition();
void TestFactorial();
void TestMultiplication();
}; // namespace TestParser

namespace TestType
{
void TestBasicTypes();
}; // namespace TestType

namespace TestTypeChecker
{
void ShowTypeError(TypeException& ex);
// void ViewExpressionTree(NamespaceList& namespaceList);
void TestMultiplication();
void TestCircleArea();
void TestSummation();
}; // namespace TestTypeChecker

namespace TestCompiler
{
void TestAddTwoNumbers();
void TestMax();
void TestFactorial();
};	 // namespace TestCompiler
#endif // TEST_HPP