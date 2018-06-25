#include "TestTypeChecker.hpp"
#include "ConstantCollector.hpp"
#include "ExpressionViewer.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "TypeChecker.hpp"
#include <iostream>
#include <string>
using std::endl;
using std::string;
using std::wcout;
void TestTypeChecker::TestMultiplication()
{
	wcout << L"TestMultiplication" << endl;
	string path = "test_cases/multiplication_function.txt";
	Lexer lexer(path);
	try
	{
		Parser parser(path, lexer.tokens);
		Module module = parser.Program();
		ConstantCollector collector;
		module.tree->Accept(&collector);
		TypeChecker checker;
		checker.global = collector.table;
		checker.current = &(checker.global);
		module.tree->Accept(&checker);
		ExpressionViewer viewer;
		module.tree->Accept(&viewer);
	}
	catch (SyntaxException& ex)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): ";
		wcout << ex.message << endl;
	}
	catch (TypeException& ex)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): ";
		wcout << ex.message << endl;
	}
	wcout << endl << endl;
}
void TestTypeChecker::TestCircleArea()
{
	wcout << L"TestCircleAreaTypeChecker" << endl;
	string path = "test_cases/CircleArea.txt";
	Lexer lexer(path);
	try
	{
		Parser parser(path, lexer.tokens);
		Module module = parser.Program();
		ConstantCollector collector;
		module.tree->Accept(&collector);
		TypeChecker checker;
		checker.global = collector.table;
		checker.current = &(checker.global);
		module.tree->Accept(&checker);
		ExpressionViewer viewer;
		module.tree->Accept(&viewer);
	}
	catch (SyntaxException& ex)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): ";
		wcout << ex.message << endl;
	}
	catch (TypeException& ex)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): ";
		wcout << ex.message << endl;
	}
	wcout << endl << endl;
}
void TestTypeChecker::TestSummation()
{
	wcout << L"TestSummation" << endl;
	string path = "test_cases/summation.txt";
	Lexer lexer(path);
	try
	{
		Parser parser(path, lexer.tokens);
		Module module = parser.Program();
		ConstantCollector collector;
		module.tree->Accept(&collector);
		TypeChecker checker;
		checker.global = collector.table;
		checker.current = &(checker.global);
		module.tree->Accept(&checker);
		ExpressionViewer viewer;
		module.tree->Accept(&viewer);
	}
	catch (SyntaxException& ex)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): ";
		wcout << ex.message << endl;
	}
	catch (TypeException& ex)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): ";
		wcout << ex.message << endl;
	}
	wcout << endl << endl;
}