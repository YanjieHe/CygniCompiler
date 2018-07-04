#ifndef PARSER_HPP
#define PARSER_HPP
#include "Exception.hpp"
#include "Expression.hpp"
#include "Namespace.hpp"
#include "Token.hpp"
#include <string>
#include <vector>
using std::string;
using std::vector;

class Parser
{
public:
	string path;
	vector<Token>& tokens;
	int32_t tokenPointer;

	Parser(string path, vector<Token>& tokens);

	CodeFile Program();

private:
	bool IsEof();
	Token& Look();
	void Move();
	void Match(Tag tag);
	wstring ParseIdentifier();
	AccessModifier ParseAM(Token& token);
	Module DefModule(AccessModifier modifier);
	Class DefClass(AccessModifier modifier);
	Function DefFunction(AccessModifier modifier);
	Parameter ParseParameter();
	LocalVariable DefLocalVariable();
	Field DefField(AccessModifier modifier);

	ExpPtr Block();
	ExpPtr If();
	ExpPtr While();
	ExpPtr Return();
	ExpPtr Statement();
	ExpPtr Assign();
	ExpPtr Or();
	ExpPtr And();
	ExpPtr Equality();
	ExpPtr Relation();
	ExpPtr Expr();
	ExpPtr Term();
	ExpPtr Unary();
	ExpPtr Postfix();
	ExpPtr Factor();
	Type ParseType();
	TypeKind ParseTypeKind(wstring text);
	vector<wstring> ParseNamespace();
};
inline bool Parser::IsEof()
{
	return Look().tag == Tag::Eof;
}
inline Token& Parser::Look()
{
	return tokens.at(tokenPointer);
}
inline void Parser::Move()
{
	int n = tokens.size() - 1;
	if (tokenPointer < n)
	{
		tokenPointer++;
	}
	else
	{
		throw SyntaxException(Look().line, Look().column, L"unexpected EOF");
	}
}
inline void Parser::Match(Tag tag)
{
	if (Look().tag == tag)
	{
		Move();
	}
	else
	{
		throw SyntaxException(Look().line, Look().column, L"syntax error");
	}
}
inline wstring Parser::ParseIdentifier()
{
	Token& token = Look();
	Match(Tag::Identifier);
	return std::any_cast<wstring>(token.value);
}
#endif // PARSER_HPP