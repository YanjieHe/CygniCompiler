#include "Lexer.hpp"
#include <unordered_map>
using std::unordered_map;
/*
  |letter | underscore | digit | other
0 |
1 |
2 |
 */
static int32_t IdentifierDFA[3][4] = {{0, 0, 0, 0}, {2, 2, 0, 0}, {2, 2, 2, 0}};
/*
	| digit | decimal point | E | + or - | L | F | other
  0 |
  1 |
  2 |
  3 |
  4 |
  5 |
  6 |
  7 |
  8 |
  9 |
 */
static int32_t NumberDFA[10][7] = {
	{0, 0, 0, 0, 0, 0, 0}, {2, 0, 0, 0, 8, 0, 0}, {2, 3, 5, 0, 8, 0, 0},
	{4, 0, 0, 0, 0, 0, 0}, {4, 0, 5, 0, 0, 0, 0}, {7, 0, 0, 6, 0, 0, 0},
	{7, 0, 0, 0, 0, 0, 0}, {7, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
};
static unordered_map<wchar_t, wchar_t> EscapedChars = {
	{L'\'', L'\''}, {L'\"', L'\"'}, {L'\\', L'\\'}, {L'n', L'\n'},
	{L'r', L'\r'},  {L't', L'\t'},  {L'b', L'\b'},  {L'f', L'\f'},
	{L'v', L'\v'},  {L'0', L'\0'},
};
Lexer::Lexer(string path)
	: reader(path)
{
	ReadAll();
}
void Lexer::ReadAll()
{
	SkipUselessChars();
	while (!reader.IsEof())
	{
		try
		{
			ReadToken();
		}
		catch (LexicalException& ex)
		{
			errorList.push_back(ex);
			SkipLine();
		}
		SkipUselessChars();
	}
	tokens.push_back(
		Token(reader.line, reader.column, Tag::Eof, wstring(L"<EOF>")));
}
void Lexer::ReadToken()
{
	wchar_t c = static_cast<wchar_t>(reader.Peek());
	if (isdigit(c))
	{
		tokens.push_back(Number());
	}
	else if (isalpha(c) || c == L'_')
	{
		tokens.push_back(Identifier());
	}
	else if (c == L'\"')
	{
		tokens.push_back(StringLiteral());
	}
	else if (c == L'\'')
	{
		tokens.push_back(CharLiteral());
	}
	else
	{
		switch (c)
		{
		case L'+':
		case L'-':
		case L'*':
		case L'/':
		case L'%':
		case L'(':
		case L')':
		case L'[':
		case L']':
		case L'{':
		case L'}':
		case L'.':
		case L',':
		case L';':
		case L':':
		case L'>':
		case L'<':
		case L'=':
		case L'!':
			tokens.push_back(Operator());
			break;
		default:
			throw LexicalException(reader.line, reader.column,
								   L"Unexpected character");
		}
	}
}
Token Lexer::Identifier()
{
	builder.Clear();
	int32_t state = 1;
	int32_t line = reader.line;
	int32_t column = reader.column;
	const int32_t LETTER = 0;
	const int32_t UNDERSCORE = 1;
	const int32_t DIGIT = 2;
	const int32_t OTHER = 3;
	while (!reader.IsEof() && state != 0)
	{
		wchar_t c = static_cast<wchar_t>(reader.Peek());
		if (isalpha(c))
		{
			Consume();
			state = IdentifierDFA[state][LETTER];
		}
		else if (c == L'_')
		{
			Consume();
			state = IdentifierDFA[state][UNDERSCORE];
		}
		else if (isdigit(c))
		{
			Consume();
			state = IdentifierDFA[state][DIGIT];
		}
		else
		{
			state = IdentifierDFA[state][OTHER];
		}
	}
	return Token::FromName(line, column, builder.ToString());
}
Token Lexer::StringLiteral()
{
	int32_t line = reader.line;
	int32_t column = reader.column;
	builder.Clear();
	reader.Read();
	while (!reader.IsEof() && reader.Peek() != L'"')
	{
		if (reader.Peek() == L'\\')
		{
			reader.Read();
			if (reader.IsEof())
			{
				throw UnterminatedStringLiteral(reader.line, reader.column);
			}
			else
			{
				wchar_t c = reader.Read();
				if (EscapedChars.find(c) != EscapedChars.end())
				{
					builder.Append(EscapedChars[c]);
				}
				else
				{
					throw LexicalException(line, column,
										   L"Unrecognized escape character");
				}
			}
		}
		else
		{
			Consume();
		}
	}
	if (reader.IsEof())
	{
		throw UnterminatedStringLiteral(reader.line, reader.column);
	}
	else
	{
		reader.Read();
		return Token(line, column, Tag::String, builder.ToString());
	}
}
Token Lexer::CharLiteral()
{
	int32_t line = reader.line;
	int32_t column = reader.column;
	reader.Read();
	if (reader.IsEof())
	{
		throw UnterminatedCharacterLiteral(reader.line, reader.column);
	}
	else
	{
		if (reader.Peek() == L'\\')
		{
			reader.Read();
			if (reader.IsEof())
			{
				throw UnterminatedCharacterLiteral(reader.line, reader.column);
			}
			else
			{
				wchar_t c = reader.Read();
				if (EscapedChars.find(c) != EscapedChars.end())
				{
					if (!reader.IsEof() && reader.Peek() == L'\'')
					{
						reader.Read();
						return Token(line, column, Tag::Char, EscapedChars[c]);
					}
					else
					{
						throw UnterminatedCharacterLiteral(reader.line,
														   reader.column);
					}
				}
				else
				{
					throw LexicalException(line, column,
										   L"Unrecognized escape character");
				}
			}
		}
		else
		{
			wchar_t c = reader.Read();
			if (!reader.IsEof() && reader.Peek() == L'\'')
			{
				reader.Read();
				return Token(line, column, Tag::Char, c);
			}
			else
			{
				throw UnterminatedCharacterLiteral(reader.line, reader.column);
			}
		}
	}
}
Token Lexer::Number()
{
	builder.Clear();
	int32_t line = reader.line;
	int32_t column = reader.column;
	const int32_t DIGIT = 0;
	const int32_t DECIMAL_POINT = 1;
	const int32_t E = 2;
	const int32_t PLUS_OR_MINUS = 3;
	const int32_t L = 4;
	const int32_t F = 5;
	const int32_t OTHER = 6;
	int32_t state = 1;
	bool accept = false;
	bool isInteger = true;
	while (!reader.IsEof() && state != 0)
	{
		if (state == 1 || state == 2 || state == 8)
		{
			isInteger = true;
			accept = true;
		}
		else if (state == 4 || state == 7 || state == 9)
		{
			isInteger = false;
			accept = true;
		}
		else
		{
			accept = false;
		}
		wchar_t c = static_cast<wchar_t>(reader.Peek());
		if (isdigit(c))
		{
			Consume();
			state = NumberDFA[state][DIGIT];
		}
		else if (c == L'.')
		{
			Consume();
			state = NumberDFA[state][DECIMAL_POINT];
		}
		else if (c == L'e' || c == L'E')
		{
			Consume();
			state = NumberDFA[state][E];
		}
		else if (c == L'+' || c == L'-')
		{
			Consume();
			state = NumberDFA[state][PLUS_OR_MINUS];
		}
		else if (c == L'L')
		{
			Consume();
			state = NumberDFA[state][L];
		}
		else if (c == L'F')
		{
			Consume();
			state = NumberDFA[state][F];
		}
		else
		{
			state = NumberDFA[state][OTHER];
		}
	}
	if (accept)
	{
		if (isInteger)
		{
			return Token::FromInteger(line, column, builder.ToString());
		}
		else
		{
			return Token::FromFloat(line, column, builder.ToString());
		}
	}
	else
	{
		throw LexicalException(line, column,
							   L"Input string was not in a correct format.");
	}
}
Token Lexer::Operator()
{
	wchar_t c = static_cast<wchar_t>(reader.Peek());
	int32_t line = reader.line;
	int32_t column = reader.column;
	switch (c)
	{
	case L'+':
	case L'-':
	case L'*':
	case L'/':
	case L'%':
	case L'(':
	case L')':
	case L'[':
	case L']':
	case L'{':
	case L'}':
	case L'.':
	case L',':
	case L';':
	case L':':
		reader.Read();
		return Token::FromOperator(line, column, CharToString(c));
	case L'>':
	case L'<':
	case L'=':
	case L'!':
	{
		reader.Read();
		if (reader.IsEof())
		{
			return Token::FromOperator(line, column, CharToString(c));
		}
		else
		{
			wchar_t c2 = static_cast<wchar_t>(reader.Peek());
			wstring text = TwoCharsToString(c, c2);
			if (operators.find(text) != operators.end())
			{
				reader.Read();
				return Token::FromOperator(line, column, text);
			}
			else
			{
				return Token::FromOperator(line, column, CharToString(c));
			}
		}
	}
	default:
		throw L"impossible branch";
	}
}
void Lexer::SkipUselessChars()
{
	while (!reader.IsEof() && (reader.Peek() == L'#' || isspace(reader.Peek())))
	{
		while (!reader.IsEof() && reader.Peek() == L'#')
		{
			while (!reader.IsEof() && reader.Peek() != L'\n')
			{
				reader.Read();
			}
			reader.Read();
		}
		while (!reader.IsEof() && isspace(reader.Peek()))
		{
			reader.Read();
		}
	}
}
void Lexer::SkipLine()
{
	if (!reader.IsEof() && reader.Peek() == L'\n')
	{
		reader.Read();
	}
	else
	{
		while (!reader.IsEof() && reader.Peek() != L'\n')
		{
			reader.Read();
		}
	}
}
wstring CharToString(wchar_t c)
{
	vector<wchar_t> characters = {c};
	return wstring(characters.begin(), characters.end());
}
wstring TwoCharsToString(wchar_t c1, wchar_t c2)
{
	vector<wchar_t> characters = {c1, c2};
	return wstring(characters.begin(), characters.end());
}