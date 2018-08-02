#ifndef SCOPE_HPP
#define SCOPE_HPP
#include "Type.hpp"
#include <any>
#include <string>
#include <unordered_map>
#include <vector>
using std::any;
using std::unordered_map;
using std::wstring;
class Scope
{
public:
	unordered_map<wstring, any> map;
	Scope();
	void Put(wstring name, any value);
};

class ScopeStack
{
public:
	vector<Scope> scopes;
	ScopeStack();
	void Push(Scope scope);
	void Pop();
	any Find(wstring name);
	bool Contains(wstring name);
	Scope& Peek();
};
#endif // SCOPE_HPP