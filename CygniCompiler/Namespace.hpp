#ifndef NAME_SPACE_HPP
#define NAME_SPACE_HPP
#include "Expression.hpp"
#include <memory>
#include <string>
#include <unordered_map>
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::weak_ptr;
class LocalVariable
{
public:
	wstring name;
	Type type;
	ExpPtr value;
	LocalVariable();
	LocalVariable(wstring name, Type type, ExpPtr value);
};
class Field
{
public:
	AccessModifier modifier;
	wstring name;
	Type type;
	ExpPtr value;
	Field();
	Field(AccessModifier modifier, wstring name, Type type, ExpPtr value);
};
class Parameter
{
public:
	wstring name;
	Type type;
	Parameter();
	Parameter(wstring name, Type type);
};
class Function
{
public:
	AccessModifier modifier;
	wstring name;
	vector<Parameter> parameters;
	vector<LocalVariable> variables;
	vector<ExpPtr> expressions;
	Type returnType;
	Type functionType;
	Function();
	Function(AccessModifier modifier, wstring name,
			 vector<Parameter> parameters, vector<LocalVariable> variables,
			 vector<ExpPtr> expressions, Type returnType);
};
class Module
{
public:
	AccessModifier modifier;
	Type type;
	vector<Field> fields;
	unordered_map<wstring, Field> fieldMap;
	unordered_map<wstring, Function> functions;
	Function moduleInitializer;
	Module();
	Module(AccessModifier modifier, Type type, vector<Field> fields,
		   unordered_map<wstring, Function> functions);
};
class Class
{
public:
	AccessModifier modifier;
	Type type;
	vector<Field> fields;
	unordered_map<wstring, Field> fieldMap;
	unordered_map<wstring, Function> functions;
	unordered_map<wstring, Function> constructors;
	Class();
	Class(AccessModifier modifier, Type type, vector<Field> fields,
		  unordered_map<wstring, Function> functions,
		  unordered_map<wstring, Function> constructors);
};
class Namespace
{
public:
	weak_ptr<Namespace> parent;
	wstring name;
	unordered_map<wstring, shared_ptr<Namespace>> subNamespaces;
	unordered_map<wstring, Module> modules;
	unordered_map<wstring, Class> classes;
	unordered_map<wstring, shared_ptr<Namespace>> uses;
	Namespace();
};

class CodeFile
{
public:
	string path;
	vector<wstring> ns;
	unordered_map<wstring, Module> modules;
	unordered_map<wstring, Class> classes;
	unordered_map<wstring, shared_ptr<Namespace>> uses;
	CodeFile(string path, vector<wstring> ns,
			 unordered_map<wstring, Module> modules,
			 unordered_map<wstring, Class> classes,
			 unordered_map<wstring, shared_ptr<Namespace>> uses);
};

class NamespaceRecord
{
public:
	unordered_map<wstring, shared_ptr<Namespace>> record;
	NamespaceRecord();
	void AddFile(CodeFile& file);
};
#endif // NAME_SPACE_HPP