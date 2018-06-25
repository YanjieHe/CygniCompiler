#include "SymbolTable.hpp"
Symbol::Symbol()
	: kind{SymbolKind::NotDefinedSymbol}
{
}
Symbol::Symbol(SymbolKind kind, any value)
	: kind{kind}
	, value{value}
{
}
SymbolTable::SymbolTable()
	: parent{nullptr}
{
}
SymbolTable::SymbolTable(SymbolTable* parent)
	: parent{parent}
{
}
Symbol Symbol::NotDefined()
{
	return Symbol(SymbolKind::NotDefinedSymbol, L"");
}
bool SymbolTable::HasSymbol(wstring name)
{
	bool found = record.find(name) != record.end();
	if (found)
	{
		return true;
	}
	else if (parent)
	{
		return parent->HasSymbol(name);
	}
	else
	{
		return false;
	}
}
void SymbolTable::Put(wstring name, Symbol symbol)
{
	bool found = record.find(name) != record.end();
	if (!found)
	{
		record[name] = symbol;
	}
}
Symbol SymbolTable::Find(wstring name)
{
	bool found = record.find(name) != record.end();
	if (found)
	{
		return record[name];
	}
	else if (parent)
	{
		return parent->Find(name);
	}
	else
	{
		return Symbol::NotDefined();
	}
}