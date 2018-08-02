#include "Scope.hpp"
#include "Exception.hpp"
Scope::Scope()
{
}
// bool Scope::Contains(wstring name)
// {
// 	bool found = map.find(name) != map.end();
// 	if (found)
// 	{
// 		return true;
// 	}
// 	else if (parent != nullptr)
// 	{
// 		return parent->Contains(name);
// 	}
// 	else
// 	{
// 		return false;
// 	}
// }
// any Scope::Get(wstring name)
// {
// 	bool found = map.find(name) != map.end();
// 	if (found)
// 	{
// 		return map[name];
// 	}
// 	else if (parent != nullptr)
// 	{
// 		return parent->Get(name);
// 	}
// 	else
// 	{
// 		throw wstring(L"not defined");
// 	}
// }
void Scope::Put(wstring name, any value)
{
	bool found = map.find(name) != map.end();
	if (found)
	{
		throw DuplicateKeyException(name);
	}
	else
	{
		map.insert({name, value});
	}
}
ScopeStack::ScopeStack()
{
}
void ScopeStack::Push(Scope scope)
{
	scopes.push_back(scope);
}
void ScopeStack::Pop()
{
	scopes.pop_back();
}
any ScopeStack::Find(wstring name)
{
	int32_t n = scopes.size();
	for (int i = n - 1; i >= 0; i--)
	{
		Scope& scope = scopes.at(i);
		bool found = scope.map.find(name) != scope.map.end();
		if (found)
		{
			return scope.map[name];
		}
	}
	throw UndefinedSymbolException(name);
}
bool ScopeStack::Contains(wstring name)
{
	int32_t n = scopes.size();
	for (int i = n - 1; i >= 0; i--)
	{
		Scope& scope = scopes.at(i);
		bool found = scope.map.find(name) != scope.map.end();
		if (found)
		{
			return true;
		}
	}
	return false;
}
Scope& ScopeStack::Peek()
{
	return scopes.back();
}