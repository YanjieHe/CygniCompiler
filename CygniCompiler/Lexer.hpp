#ifndef LEXER_HPP
#define LEXER_HPP
#include "Exception.hpp"
#include "SourceReader.hpp"
#include "StringBuilder.hpp"
#include "Token.hpp"
#include <cstdint>
#include <string>
#include <vector>
using std::string;
using std::vector;
class Lexer
{
public:
	vector<LexicalException> errorList;
	vector<Token> tokens;
	Lexer(string path);

private:
	SourceReader reader;
	StringBuilder builder;

	void ReadAll();
	void Consume();
	void ReadToken();
	Token Identifier();
	Token StringLiteral();
	Token CharLiteral();
	Token Number();
	Token Operator();
	void SkipUselessChars();
	void SkipLine();
};
inline void Lexer::Consume()
{
	builder.Append(reader.Read());
}
wstring CharToString(wchar_t c);
wstring TwoCharsToString(wchar_t c1, wchar_t c2);
#endif // LEXER_HPP