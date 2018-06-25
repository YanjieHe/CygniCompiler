#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include <cstdint>
#include <string>
using std::wstring;
class Exception
{
public:
	wstring message;
	Exception(wstring message);
};
class LexicalException : public Exception
{
public:
	int32_t line;
	int32_t column;
	LexicalException(int32_t line, int32_t column, wstring message);
};
LexicalException IntegerTooLarge(int32_t line, int32_t column);
LexicalException FloatTooLarge(int32_t line, int32_t column);
LexicalException UnterminatedStringLiteral(int32_t line, int32_t column);
LexicalException UnterminatedCharacterLiteral(int32_t line, int32_t column);
class SyntaxException : public Exception
{
public:
	int32_t line;
	int32_t column;
	SyntaxException(int32_t line, int32_t column, wstring message);
};
class TypeException : public Exception
{
public:
	int32_t line;
	int32_t column;
	TypeException(int32_t line, int32_t column, wstring message);
};
class FileNotFoundException : public Exception
{
public:
	FileNotFoundException();
};

#endif // EXCEPTION_HPP