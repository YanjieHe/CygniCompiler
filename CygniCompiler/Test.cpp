#include "Test.hpp"
#include "ExpressionViewer.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Type.hpp"
#include "TypeChecker.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::any_cast;
using std::endl;
using std::string;
using std::vector;
using std::wcout;
void TestLexer::AssertEqual(vector<Token>& x, vector<Token>& y, wstring message)
{
	if (x != y)
	{
		wcout << message << endl;
	}
}
void TestLexer::ShowTokens(vector<Token>& tokens)
{
	for (Token& token : tokens)
	{
		wcout << L"(" << token.line;
		wcout << L", " << token.column;
		wcout << L", " << TokenTagToString(token.tag);
		if (token.value.type() == typeid(int32_t))
		{
			wcout << L", " << any_cast<int32_t>(token.value);
		}
		else if (token.value.type() == typeid(int64_t))
		{
			wcout << L", " << any_cast<int64_t>(token.value);
		}
		else if (token.value.type() == typeid(float))
		{
			wcout << L", " << any_cast<float>(token.value);
		}
		else if (token.value.type() == typeid(double))
		{
			wcout << L", " << any_cast<double>(token.value);
		}
		else if (token.value.type() == typeid(wchar_t))
		{
			wcout << L", " << any_cast<wchar_t>(token.value);
		}
		else
		{
			wcout << L", " << any_cast<wstring>(token.value);
		}
		wcout << L")" << endl;
	}
}
void TestLexer::ShowErrors(vector<LexicalException>& errors)
{
	for (auto& ex : errors)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): " << ex.message
			  << endl;
	}
}
void TestLexer::TestNumber()
{
	string path = "test_cases/number_test.txt";
	wcout << L"Test Function: " << __FUNCTION__ << endl;
	Lexer lexer(path);
	ShowTokens(lexer.tokens);
	vector<Token> expected = {Token(1, 1, Tag::Int, int32_t(12)),
							  Token(1, 4, Tag::Double, double(34.3)),
							  Token(1, 9, Tag::Double, double(4e08)),
							  Token(2, 1, Tag::Long, int64_t(32)),
							  Token(2, 5, Tag::Float, float(2.34)),
							  Token(3, 1, Tag::Eof, wstring(L"<EOF>"))};
	AssertEqual(lexer.tokens, expected, L"test number fails");
}
void TestLexer::TestHelloWorld()
{
	string path = "test_cases/hello_world_test.txt";
	wcout << L"Test Function: " << __FUNCTION__ << endl;
	Lexer lexer(path);
	ShowTokens(lexer.tokens);
	ShowErrors(lexer.errorList);
	// vector<Token> expected = {
	// 	Token(1, 1, Tag::DefFun, wstring(L"fun")),
	// 	Token(1, 5, Tag::Identifier, wstring(L"Main")),
	// 	Token(1, 9, Tag::LeftParenthesis, wstring(L"(")),
	// 	Token(1, 10, Tag::Identifier, L"args"),
	// };
}
void TestParser::ShowSyntaxError(SyntaxException& ex)
{
	wcout << L"(" << ex.line << L", " << ex.column << L"): ";
	wcout << ex.message << endl;
}
void TestParser::ViewNamespaceRecord(NamespaceRecord& nsRecord)
{
	ExpressionViewer viewer;
	for (auto& pair : nsRecord.record)
	{
		auto nsPtr = pair.second;
		viewer.ViewNamespace(nsPtr);
	}
}
void TestParser::TestSimpleArithmetic()
{
	wcout << L"Test Function: " << __FUNCTION__ << endl;
	ExpPtr x =
		Ast::Multiply(0, 0, Ast::Constant(0, 0, 17), Ast::Constant(0, 0, 18));
	ExpPtr y =
		Ast::Divide(0, 0, Ast::Constant(0, 0, 17), Ast::Constant(0, 0, 18));
	ExpPtr exp = Ast::Add(0, 0, x, y);
	ExpressionViewer viewer;
	exp->Accept(&viewer);
	wcout << endl << endl;
}
void TestParser::TestAddition()
{
	wcout << L"Test Function: " << __FUNCTION__ << endl;
	string path = "test_cases/addition_function.txt";
	Lexer lexer(path);
	try
	{
		Parser parser(path, lexer.tokens);
		NamespaceRecord nsRecord;
		CodeFile file = parser.Program();
		nsRecord.AddFile(file);
		TypeChecker checker(nsRecord);
		ViewNamespaceRecord(nsRecord);
	}
	catch (SyntaxException& ex)
	{
		ShowSyntaxError(ex);
	}
	wcout << endl << endl;
}
void TestParser::TestFactorial()
{
	wcout << L"Test Function: " << __FUNCTION__ << endl;
	string path = "test_cases/factorial_function.txt";
	Lexer lexer(path);
	try
	{
		Parser parser(path, lexer.tokens);
		NamespaceRecord nsRecord;
		CodeFile file = parser.Program();
		nsRecord.AddFile(file);
		TypeChecker checker(nsRecord);
		ViewNamespaceRecord(nsRecord);
	}
	catch (SyntaxException& ex)
	{
		ShowSyntaxError(ex);
	}
	catch (TypeException& ex)
	{
		TestTypeChecker::ShowTypeError(ex);
	}
	wcout << endl << endl;
}
void TestParser::TestMultiplication()
{
	wcout << L"TestMultiplication" << endl;
	string path = "test_cases/multiplication_function.txt";
	Lexer lexer(path);
	try
	{
		Parser parser(path, lexer.tokens);
		CodeFile file = parser.Program();
		ExpressionViewer viewer;
		// for (auto& module : file.modules)
		// {
		// 	module->Accept(&viewer);
		// }
		// for (auto& _class : file.classes)
		// {
		// 	_class->Accept(&viewer);
		// }
	}
	catch (SyntaxException& ex)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): ";
		wcout << ex.message << endl;
	}
	wcout << endl << endl;
}

void TestType::TestBasicTypes()
{
	Type intType = Type::Int();
	Type arrayType = Type::Array(intType);
	if (TypeToString(intType) != L"Int")
	{
		wcout << L"TestBasicTypes Int fails" << endl;
	}
	if (TypeToString(arrayType) != L"Array[Int]")
	{
		wcout << L"TestBasicTypes Int fails" << endl;
	}
}
void TestTypeChecker::ShowTypeError(TypeException& ex)
{
	wcout << L"(" << ex.line << L", " << ex.column << L"): ";
	wcout << ex.message << endl;
}

// void TestTypeChecker::ViewExpressionTree(NamespaceList& namespaceList)
// {
// 	ExpressionViewer viewer;
// 	for (Namespace& _namespace : namespaceList.list)
// 	{
// 		for (auto& codeFile : _namespace.files)
// 		{
// 			for (auto& module : codeFile.modules)
// 			{
// 				module->Accept(&viewer);
// 			}
// 			for (auto& _class : codeFile.classes)
// 			{
// 				_class->Accept(&viewer);
// 			}
// 		}
// 	}
// }
void TestTypeChecker::TestMultiplication()
{
	wcout << L"TestMultiplication" << endl;
	string path = "test_cases/multiplication_function.txt";
	Lexer lexer(path);
	try
	{
		Parser parser(path, lexer.tokens);
		NamespaceRecord nsRecord;
		CodeFile file = parser.Program();
		nsRecord.AddFile(file);
		TypeChecker checker(nsRecord);
		TestParser::ViewNamespaceRecord(nsRecord);
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
		NamespaceRecord nsRecord;
		CodeFile file = parser.Program();
		nsRecord.AddFile(file);
		TypeChecker checker(nsRecord);
		TestParser::ViewNamespaceRecord(nsRecord);
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
		CodeFile codeFile = parser.Program();
		// Namespace _namespace(codeFile.name);
		// _namespace.AddCodeFile(codeFile);
		// NamespaceList nameSpaceList;
		// nameSpaceList.Add(_namespace);
		// TypeChecker checker(nameSpaceList);
		// ViewExpressionTree(nameSpaceList);
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