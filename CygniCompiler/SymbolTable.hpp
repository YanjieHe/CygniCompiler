#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP
#include <any>
#include <memory>
#include <string>
#include <unordered_map>
using std::any;
using std::shared_ptr;
using std::unordered_map;
using std::wstring;

enum class SymbolKind
{
	NotDefinedSymbol,
	VariableSymbol,
	FunctionSymbol,
	TypeSymbol
};
class Symbol
{
public:
	SymbolKind kind;
	any value;
	Symbol();
	Symbol(SymbolKind kind, any value);
	static Symbol NotDefined();
};
class SymbolTable
{
public:
	SymbolTable* parent;
	unordered_map<wstring, Symbol> record;

	SymbolTable();
	SymbolTable(SymbolTable* parent);
	bool HasSymbol(wstring name);
	void Put(wstring name, Symbol symbol);
	Symbol Find(wstring name);
};
#endif // SYMBOL_TABLE_HPP