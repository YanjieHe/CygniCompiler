#include "Namespace.hpp"
using std::make_shared;
LocalVariable::LocalVariable()
{
}
LocalVariable::LocalVariable(wstring name, Type type, ExpPtr value)
	: name{name}
	, type{type}
	, value{value}
{
}
Field::Field()
{
}
Field::Field(AccessModifier modifier, wstring name, Type type, ExpPtr value)
	: modifier{modifier}
	, name{name}
	, type{type}
	, value{value}
{
}
Parameter::Parameter()
{
}
Parameter::Parameter(wstring name, Type type)
	: name{name}
	, type{type}
{
}
Function::Function()
{
}
Function::Function(AccessModifier modifier, wstring name,
				   vector<Parameter> parameters,
				   vector<LocalVariable> variables, vector<ExpPtr> expressions,
				   Type returnType)
	: modifier{modifier}
	, name{name}
	, parameters{parameters}
	, variables{variables}
	, expressions{expressions}
	, returnType{returnType}
{
	vector<Type> types;
	types.reserve(parameters.size() + 1);
	for (int i = 0, n = parameters.size(); i < n; i++)
	{
		types.push_back(parameters.at(i).type);
	}
	types.push_back(returnType);
	this->functionType = Type::Function(types);
}
Module::Module()
{
}
Module::Module(AccessModifier modifier, Type type, vector<Field> fields,
			   unordered_map<wstring, Function> functions)
	: modifier{modifier}
	, type{type}
	, fields{fields}
	, functions{functions}
{
	for (Field field : fields)
	{
		fieldMap.insert({field.name, field});
	}
}
Class::Class()
{
}
Class::Class(AccessModifier modifier, Type type, vector<Field> fields,
			 unordered_map<wstring, Function> functions,
			 unordered_map<wstring, Function> constructors)
	: modifier{modifier}
	, type{type}
	, fields{fields}
	, functions{functions}
	, constructors{constructors}
{
	for (Field field : fields)
	{
		fieldMap.insert({field.name, field});
	}
}
Namespace::Namespace()
{
}
CodeFile::CodeFile(string path, vector<wstring> ns,
				   unordered_map<wstring, Module> modules,
				   unordered_map<wstring, Class> classes,
				   unordered_map<wstring, shared_ptr<Namespace>> uses)
	: path{path}
	, ns{ns}
	, modules{modules}
	, classes{classes}
	, uses{uses}
{
}
NamespaceRecord::NamespaceRecord()
{
}
void NamespaceRecord::AddFile(CodeFile& file)
{
	bool found = record.find(file.ns.front()) != record.end();
	if (found)
	{
		shared_ptr<Namespace> nsPtr = record[file.ns.front()];
		for (int i = 1, size = file.ns.size(); i < size; i++)
		{
			wstring subNs = file.ns.at(i);
			found =
				nsPtr->subNamespaces.find(subNs) != nsPtr->subNamespaces.end();
			if (found)
			{
				nsPtr = nsPtr->subNamespaces[subNs];
			}
			else
			{
				shared_ptr<Namespace> subNsPtr = make_shared<Namespace>();
				subNsPtr->parent = nsPtr;
				subNsPtr->name = subNs;
				nsPtr = subNsPtr;
			}
		}
		nsPtr->modules = file.modules;
		nsPtr->classes = file.classes;
		nsPtr->uses = file.uses;
	}
	else
	{
		shared_ptr<Namespace> nsPtr = make_shared<Namespace>();
		nsPtr->name = file.ns.front();
		for (int i = 1, size = file.ns.size(); i < size; i++)
		{
			wstring subNs = file.ns.at(i);
			shared_ptr<Namespace> subNsPtr = make_shared<Namespace>();
			subNsPtr->parent = nsPtr;
			subNsPtr->name = subNs;
			nsPtr = subNsPtr;
		}
		nsPtr->modules = file.modules;
		nsPtr->classes = file.classes;
		nsPtr->uses = file.uses;
		record.insert({nsPtr->name, nsPtr});
	}
}