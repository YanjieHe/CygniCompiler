#include "TestParser.hpp"
#include "ExpressionViewer.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include <iostream>
#include <string>
using std::endl;
using std::string;
using std::wcout;
void TestSimpleArithmetic()
{
	wcout << L"TestSimpleArithmetic" << endl;
	ExpPtr x =
		Ast::Multiply(0, 0, Ast::Constant(0, 0, 17), Ast::Constant(0, 0, 18));
	ExpPtr y =
		Ast::Divide(0, 0, Ast::Constant(0, 0, 17), Ast::Constant(0, 0, 18));
	ExpPtr exp = Ast::Add(0, 0, x, y);
	ExpressionViewer viewer;
	exp->Accept(&viewer);
	wcout << endl << endl;
}
void TestAddition()
{
	wcout << L"TestAddition" << endl;
	string path = "test_cases/addition_function.txt";
	Lexer lexer(path);
	try
	{
		Parser parser(path, lexer.tokens);
		Module module = parser.Program();
		ExpressionViewer viewer;
		module.tree->Accept(&viewer);
	}
	catch (SyntaxException& ex)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): ";
		wcout << ex.message << endl;
	}
	wcout << endl << endl;
}
void TestFactorial()
{
	wcout << L"TestFactorial" << endl;
	string path = "test_cases/factorial_function.txt";
	Lexer lexer(path);
	try
	{
		Parser parser(path, lexer.tokens);
		Module module = parser.Program();
		ExpressionViewer viewer;
		module.tree->Accept(&viewer);
	}
	catch (SyntaxException& ex)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): ";
		wcout << ex.message << endl;
	}
	wcout << endl << endl;
}
void TestMultiplication()
{
	wcout << L"TestMultiplication" << endl;
	string path = "test_cases/multiplication_function.txt";
	Lexer lexer(path);
	try
	{
		Parser parser(path, lexer.tokens);
		Module module = parser.Program();
		ExpressionViewer viewer;
		module.tree->Accept(&viewer);
	}
	catch (SyntaxException& ex)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): ";
		wcout << ex.message << endl;
	}
	wcout << endl << endl;
}