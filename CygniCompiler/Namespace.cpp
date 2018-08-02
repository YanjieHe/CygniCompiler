#include "Namespace.hpp"
#include <iostream>
using std::endl;
using std::make_shared;
using std::wcout;
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
	for (int32_t i = 0, n = parameters.size(); i < n; i++)
	{
		types.push_back(parameters.at(i).type);
	}
	types.push_back(returnType);
	this->functionType = Type::Function(types);
}
NativeFunction::NativeFunction()
{
}
NativeFunction::NativeFunction(wstring libraryPath, wstring functionName,
							   wstring options, AccessModifier modifier,
							   wstring name, vector<Parameter> parameters,
							   Type returnType)
	: libraryPath{libraryPath}
	, functionName{functionName}
	, options{options}
	, modifier{modifier}
	, name{name}
	, parameters{parameters}
	, returnType{returnType}
{
	vector<Type> types;
	types.reserve(parameters.size() + 1);
	for (int32_t i = 0, n = parameters.size(); i < n; i++)
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
			   vector<Function> functions,
			   vector<NativeFunction> nativeFunctions)
	: modifier{modifier}
	, type{type}
	, fields{fields}
	, functions{functions}
	, nativeFunctions{nativeFunctions}
{
	for (int32_t i = 0, n = fields.size(); i < n; i++)
	{
		fieldMap.insert({fields[i].name, i});
	}
	for (int32_t i = 0, n = functions.size(); i < n; i++)
	{
		functionMap.insert({functions[i].name, i});
	}
	for (int32_t i = 0, n = nativeFunctions.size(); i < n; i++)
	{
		nativeFunctionMap.insert({nativeFunctions[i].name, i});
	}
}
Class::Class()
{
}
Class::Class(AccessModifier modifier, Type type, vector<Field> fields,
			 vector<Function> functions,
			 unordered_map<wstring, Function> constructors)
	: modifier{modifier}
	, type{type}
	, fields{fields}
	, functions{functions}
	, constructors{constructors}
{
	for (int32_t i = 0, n = fields.size(); i < n; i++)
	{
		fieldMap.insert({fields[i].name, i});
	}
	for (int32_t i = 0, n = functions.size(); i < n; i++)
	{
		functionMap.insert({functions[i].name, i});
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
		for (int32_t i = 1, size = file.ns.size(); i < size; i++)
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
		for (auto& p : file.modules)
		{
			nsPtr->modules.insert({p.first, p.second});
		}
		for (auto& p : file.classes)
		{
			nsPtr->classes.insert({p.first, p.second});
		}
		for (auto& p : file.uses)
		{
			nsPtr->uses.insert({p.first, p.second});
		}
	}
	else
	{
		shared_ptr<Namespace> nsPtr = make_shared<Namespace>();
		nsPtr->name = file.ns.front();
		for (int32_t i = 1, size = file.ns.size(); i < size; i++)
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