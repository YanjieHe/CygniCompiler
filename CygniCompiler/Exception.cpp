#include "Exception.hpp"
Exception::Exception(wstring message)
	: message{message}
{
}
LexicalException::LexicalException(int32_t line, int32_t column,
								   wstring message)
	: Exception(message)
	, line{line}
	, column{column}
{
}
LexicalException IntegerTooLarge(int32_t line, int32_t column)
{
	return LexicalException(line, column, L"Integral constant is too large");
}
LexicalException FloatTooLarge(int32_t line, int32_t column)
{
	// Floating-point constant is outside the range of type `double'
	return LexicalException(line, column,
							L"Floating-point constant is too large");
}
LexicalException UnterminatedStringLiteral(int32_t line, int32_t column)
{
	return LexicalException(line, column, L"Unterminated string literal");
}
LexicalException UnterminatedCharacterLiteral(int32_t line, int32_t column)
{
	return LexicalException(line, column, L"Unterminated character literal");
}
SyntaxException::SyntaxException(int32_t line, int32_t column, wstring message)
	: Exception(message)
	, line{line}
	, column{column}
{
}
TypeException::TypeException(int32_t line, int32_t column, wstring message)
	: Exception(message)
	, line{line}
	, column{column}
{
}
FileNotFoundException::FileNotFoundException()
	: Exception(L"Unable to find the specified file")
{
}
NotImplementedException::NotImplementedException()
	: Exception(L"The method or operation is not implemented")
{
}
UndefinedSymbolException::UndefinedSymbolException(wstring name)
	: Exception(L"undefined symbol " + name)
{
}
DuplicateKeyException::DuplicateKeyException(wstring key)
	: Exception(L"duplicate key " + key)
{
}