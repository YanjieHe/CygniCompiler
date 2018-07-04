#ifndef SCOPE_HPP
#define SCOPE_HPP
#include "Type.hpp"
#include <any>
#include <string>
#include <unordered_map>
using std::any;
using std::unordered_map;
using std::wstring;
class Scope
{
public:
	Scope* parent;
	unordered_map<wstring, any> map;

	Scope(Scope* parent);

	bool Contains(wstring name);
	any Get(wstring name);
	bool Put(wstring name, any value);
};
#endif // SCOPE_HPP