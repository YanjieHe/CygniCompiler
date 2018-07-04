#include "Scope.hpp"
Scope::Scope(Scope* parent)
	: parent{parent}
{
}
bool Scope::Contains(wstring name)
{
	bool found = map.find(name) != map.end();
	if (found)
	{
		return true;
	}
	else if (parent != nullptr)
	{
		return parent->Contains(name);
	}
	else
	{
		return false;
	}
}
any Scope::Get(wstring name)
{
	bool found = map.find(name) != map.end();
	if (found)
	{
		return map[name];
	}
	else if (parent != nullptr)
	{
		return parent->Get(name);
	}
	else
	{
		throw wstring(L"not defined");
	}
}
bool Scope::Put(wstring name, any value)
{
	bool found = map.find(name) != map.end();
	if (found)
	{
		return false;
	}
	else
	{
		map.insert({name, value});
		return true;
	}
}