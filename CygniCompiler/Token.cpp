#include "Token.hpp"
#include "Exception.hpp"
#include <iostream>
#include <numeric>
#include <stdexcept>
using std::any_cast;
using std::endl;
using std::numeric_limits;
using std::out_of_range;
using std::stod;
using std::stof;
using std::stol;
using std::wcout;
Token::Token(int32_t line, int32_t column, Tag tag, any value)
	: line{line}
	, column{column}
	, tag{tag}
	, value{value}
{
}
Token Token::FromName(int32_t line, int32_t column, wstring name)
{
	if (keywords.find(name) != keywords.end())
	{
		return Token(line, column, keywords[name], name);
	}
	else
	{
		return Token(line, column, Tag::Identifier, name);
	}
}
Token Token::FromInteger(int32_t line, int32_t column, wstring text)
{
	if (text.back() == L'L')
	{
		text.pop_back();
		try
		{
			int64_t value = stol(text);
			return Token(line, column, Tag::Long, value);
		}
		catch (out_of_range& ex)
		{
			throw IntegerTooLarge(line, column);
		}
	}
	else
	{
		try
		{
			int64_t value = stol(text);
			if (value > numeric_limits<int32_t>::max())
			{
				return Token(line, column, Tag::Long, int64_t(value));
			}
			else
			{
				return Token(line, column, Tag::Int,
							 static_cast<int32_t>(value));
			}
		}
		catch (out_of_range& ex)
		{
			throw IntegerTooLarge(line, column);
		}
	}
}
Token Token::FromFloat(int32_t line, int32_t column, wstring text)
{
	if (text.back() == L'F')
	{
		text.pop_back();
		try
		{
			float value = stof(text);
			return Token(line, column, Tag::Float, static_cast<float>(value));
		}
		catch (out_of_range& ex)
		{
			throw FloatTooLarge(line, column);
		}
	}
	else
	{
		try
		{
			double value = stod(text);
			return Token(line, column, Tag::Double, value);
		}
		catch (out_of_range& ex)
		{
			throw FloatTooLarge(line, column);
		}
	}
}
Token Token::FromOperator(int32_t line, int32_t column, wstring text)
{
	if (operators.find(text) != operators.end())
	{
		return Token(line, column, operators[text], text);
	}
	else
	{
		throw LexicalException(line, column, L"Not supported operator");
	}
}
bool operator==(const Token& x, const Token& y)
{
	if (x.line == y.line && x.column == y.column && x.tag == y.tag)
	{
		if (x.value.type() == y.value.type())
		{
			if (x.value.type() == typeid(int32_t))
			{
				return any_cast<int32_t>(x.value) == any_cast<int32_t>(y.value);
			}
			else if (x.value.type() == typeid(int64_t))
			{
				return any_cast<int64_t>(x.value) == any_cast<int64_t>(y.value);
			}
			else if (x.value.type() == typeid(float))
			{
				return any_cast<float>(x.value) == any_cast<float>(y.value);
			}
			else if (x.value.type() == typeid(double))
			{
				return any_cast<double>(x.value) == any_cast<double>(y.value);
			}
			else if (x.value.type() == typeid(bool))
			{
				return any_cast<bool>(x.value) == any_cast<bool>(y.value);
			}
			else if (x.value.type() == typeid(wchar_t))
			{
				return any_cast<wchar_t>(x.value) == any_cast<wchar_t>(y.value);
			}
			else
			{
				return any_cast<wstring>(x.value) == any_cast<wstring>(y.value);
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
wstring TokenTagToString(Tag tag)
{
	switch (tag)
	{
	case Tag::Eof:
		return L"Eof";
	case Tag::Int:
		return L"Int";
	case Tag::Long:
		return L"Long";
	case Tag::Float:
		return L"Float";
	case Tag::Double:
		return L"Double";
	case Tag::Char:
		return L"Char";
	case Tag::String:
		return L"String";
	case Tag::Identifier:
		return L"Identifier";
	case Tag::True:
		return L"True";
	case Tag::False:
		return L"False";
	case Tag::Add:
		return L"Add";
	case Tag::Subtract:
		return L"Subtract";
	case Tag::Multiply:
		return L"Multiply";
	case Tag::Divide:
		return L"Divide";
	case Tag::Modulo:
		return L"Modulo";
	case Tag::Equal:
		return L"Equal";
	case Tag::NotEqual:
		return L"NotEqual";
	case Tag::GreaterThan:
		return L"GreaterThan";
	case Tag::GreaterThanOrEqual:
		return L"GreaterThanOrEqual";
	case Tag::LessThan:
		return L"LessThan";
	case Tag::LessThanOrEqual:
		return L"LessThanOrEqual";
	case Tag::And:
		return L"And";
	case Tag::Or:
		return L"Or";
	case Tag::Not:
		return L"Not";
	case Tag::DefVar:
		return L"DefVar";
	case Tag::DefFun:
		return L"DefFun";
	case Tag::Assign:
		return L"Assign";
	case Tag::LeftBrace:
		return L"LeftBrace";
	case Tag::RightBrace:
		return L"RightBrace";
	case Tag::LeftBracket:
		return L"LeftBracket";
	case Tag::RightBracket:
		return L"RightBracket";
	case Tag::LeftParenthesis:
		return L"LeftParenthesis";
	case Tag::RightParenthesis:
		return L"RightParenthesis";
	case Tag::Dot:
		return L"Dot";
	case Tag::Comma:
		return L"Comma";
	case Tag::Semicolon:
		return L"Semicolon";
	case Tag::Colon:
		return L"Colon";
	case Tag::If:
		return L"If";
	case Tag::Else:
		return L"Else";
	case Tag::While:
		return L"While";
	case Tag::For:
		return L"For";
	case Tag::Break:
		return L"Break";
	case Tag::Return:
		return L"Return";
	case Tag::Class:
		return L"Class";
	case Tag::Public:
		return L"Public";
	case Tag::Private:
		return L"Private";
	case Tag::Protected:
		return L"Protected";
	default:
		throw wstring(L"Error");
	}
}