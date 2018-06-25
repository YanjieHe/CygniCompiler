#include "TestLexer.hpp"
#include <iostream>
using std::any_cast;
using std::endl;
using std::string;
using std::wcout;
void AssertEqual(vector<Token>& x, vector<Token>& y, wstring message)
{
	if (x != y)
	{
		wcout << message << endl;
	}
}
void ShowTokens(vector<Token>& tokens)
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
void TestNumber()
{
	string path = "test_cases/number_test.txt";
	Lexer lexer(path);
	// ShowTokens(lexer.tokens);
	vector<Token> expected = {Token(1, 1, Tag::Int, int32_t(12)),
							  Token(1, 4, Tag::Double, double(34.3)),
							  Token(1, 9, Tag::Double, double(4e08)),
							  Token(2, 1, Tag::Long, int64_t(32)),
							  Token(2, 5, Tag::Float, float(2.34)),
							  Token(3, 1, Tag::Eof, wstring(L"<EOF>"))};
	AssertEqual(lexer.tokens, expected, L"test number fails");
}
void TestHelloWorld()
{
	string path = "test_cases/hello_world_test.txt";
	Lexer lexer(path);
	ShowTokens(lexer.tokens);
	for (auto& ex : lexer.errorList)
	{
		wcout << L"(" << ex.line << L", " << ex.column << L"): " << ex.message
			  << endl;
	}
}