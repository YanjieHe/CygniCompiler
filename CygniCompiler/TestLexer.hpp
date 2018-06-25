#ifndef TEST_LEXER_HPP
#define TEST_LEXER_HPP
#include "Lexer.hpp"
#include <string>
#include <vector>
using std::vector;
using std::wstring;
void AssertEqual(vector<Token>& x, vector<Token>& y, wstring message);
void ShowTokens(vector<Token>& tokens);
void TestNumber();
void TestHelloWorld();
#endif // TEST_LEXER_HPP