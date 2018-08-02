#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <any>
#include <string>
#include <unordered_map>
using std::any;
using std::unordered_map;
using std::wstring;
enum class Tag
{
	Eof,
	Int,
	Long,
	Float,
	Double,
	Char,
	String,
	Identifier,
	True,
	False,

	Add,
	Subtract,
	Multiply,
	Divide,
	Modulo,

	Equal,
	NotEqual,
	GreaterThan,
	GreaterThanOrEqual,
	LessThan,
	LessThanOrEqual,

	And,
	Or,
	Not,

	DefVar,
	DefFun,
	Assign,

	LeftBrace,
	RightBrace,
	LeftBracket,
	RightBracket,
	LeftParenthesis,
	RightParenthesis,

	Dot,
	Comma,
	Semicolon,
	Colon,

	If,
	Else,
	While,

	For,
	Break,
	Return,

	Class,
	Public,
	Private,
	Protected,
	Internal,

	Module,
	Namespace,
	Uses,
	Native,
};

class Token
{
public:
	int32_t line;
	int32_t column;
	Tag tag;
	any value;
	Token(int32_t line, int32_t column, Tag tag, any value);
	static Token FromName(int32_t line, int32_t column, wstring name);
	static Token FromInteger(int32_t line, int32_t column, wstring text);
	static Token FromFloat(int32_t line, int32_t column, wstring text);
	static Token FromOperator(int32_t line, int32_t column, wstring text);
};
bool operator==(const Token& x, const Token& y);
static unordered_map<wstring, Tag> keywords = {{L"true", Tag::True},
											   {L"false", Tag::False},
											   {L"var", Tag::DefVar},
											   {L"fun", Tag::DefFun},
											   {L"and", Tag::And},
											   {L"or", Tag::Or},
											   {L"not", Tag::Not},
											   {L"if", Tag::If},
											   {L"else", Tag::Else},
											   {L"while", Tag::While},
											   {L"return", Tag::Return},
											   {L"class", Tag::Class},
											   {L"public", Tag::Public},
											   {L"private", Tag::Private},
											   {L"protected", Tag::Protected},
											   {L"internal", Tag::Internal},
											   {L"module", Tag::Module},
											   {L"namespace", Tag::Namespace},
											   {L"uses", Tag::Uses},
											   {L"native", Tag::Native}};

static unordered_map<wstring, Tag> operators = {
	{L"+", Tag::Add},
	{L"-", Tag::Subtract},
	{L"*", Tag::Multiply},
	{L"/", Tag::Divide},
	{L"%", Tag::Modulo},
	{L"=", Tag::Assign},
	{L"==", Tag::Equal},
	{L"!=", Tag::NotEqual},
	{L">", Tag::GreaterThan},
	{L"<", Tag::LessThan},
	{L">=", Tag::GreaterThanOrEqual},
	{L"<=", Tag::LessThanOrEqual},
	{L"(", Tag::LeftParenthesis},
	{L")", Tag::RightParenthesis},
	{L"[", Tag::LeftBracket},
	{L"]", Tag::RightBracket},
	{L"{", Tag::LeftBrace},
	{L"}", Tag::RightBrace},
	{L".", Tag::Dot},
	{L",", Tag::Comma},
	{L";", Tag::Semicolon},
	{L":", Tag::Colon}};

wstring TokenTagToString(Tag tag);
#endif // TOKEN_HPP
