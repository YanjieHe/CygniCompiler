#include "Type.hpp"
Type::Type()
	: kind{TypeKind::Unknown}
	, name{L"Unknown"}
{
}
Type::Type(TypeKind kind, wstring name, vector<Type> parameters)
	: kind{kind}
	, name{name}
	, parameters(parameters)
{
}
Type Type::Int()
{
	static Type type = Type(TypeKind::Int, L"Int", vector<Type>());
	return type;
}
Type Type::Long()
{
	static Type type = Type(TypeKind::Long, L"Long", vector<Type>());
	return type;
}
Type Type::Float()
{
	static Type type = Type(TypeKind::Float, L"Float", vector<Type>());
	return type;
}
Type Type::Double()
{
	static Type type = Type(TypeKind::Double, L"Double", vector<Type>());
	return type;
}
Type Type::Boolean()
{
	static Type type = Type(TypeKind::Boolean, L"Boolean", vector<Type>());
	return type;
}
Type Type::Char()
{
	static Type type = Type(TypeKind::Char, L"Char", vector<Type>());
	return type;
}
Type Type::String()
{
	static Type type = Type(TypeKind::String, L"String", vector<Type>());
	return type;
}
Type Type::Unit()
{
	static Type type = Type(TypeKind::Unit, L"Unit", vector<Type>());
	return type;
}
Type Type::Array(Type elementType)
{
	return Type(TypeKind::Array, L"Array", vector<Type>{elementType});
}
Type Type::Function(vector<Type> parameters)
{
	return Type(TypeKind::Function, L"Function", parameters);
}
Type Type::Module(wstring name, vector<Type> parameters)
{
	return Type(TypeKind::Module, name, parameters);
}
Type Type::Class(wstring name, vector<Type> parameters)
{
	return Type(TypeKind::Class, name, parameters);
}
Type Type::Namespace(wstring name)
{
	return Type(TypeKind::Namespace, name, vector<Type>());
}
Type Type::Object(wstring name, vector<Type> parameters)
{
	return Type(TypeKind::Object, name, parameters);
}
bool Type::IsInt()
{
	return kind == TypeKind::Int;
}
bool Type::IsLong()
{
	return kind == TypeKind::Long;
}
bool Type::IsFloat()
{
	return kind == TypeKind::Float;
}
bool Type::IsDouble()
{
	return kind == TypeKind::Double;
}
bool Type::IsBoolean()
{
	return kind == TypeKind::Boolean;
}
bool Type::IsChar()
{
	return kind == TypeKind::Char;
}
bool Type::IsString()
{
	return kind == TypeKind::String;
}
bool Type::IsUnit()
{
	return kind == TypeKind::Unit;
}
bool Type::IsArray()
{
	return kind == TypeKind::Array;
}
bool Type::IsFunction()
{
	return kind == TypeKind::Function;
}
bool Type::IsModule()
{
	return kind == TypeKind::Module;
}
bool Type::IsClass()
{
	return kind == TypeKind::Class;
}
bool Type::IsNamespace()
{
	return kind == TypeKind::Namespace;
}
bool Type::IsObject()
{
	return kind == TypeKind::Object;
}
wstring TypeToString(Type& type)
{
	if (type.parameters.size() == 0)
	{
		return type.name;
	}
	else
	{
		vector<wchar_t> vec;
		for (wchar_t c : type.name)
		{
			vec.push_back(c);
		}
		vec.push_back(L'[');
		for (wchar_t c : TypeToString(type.parameters.front()))
		{
			vec.push_back(c);
		}
		for (int32_t i = 1, n = type.parameters.size(); i < n; i++)
		{
			vec.push_back(L',');
			vec.push_back(L' ');
			for (wchar_t c : TypeToString(type.parameters.at(i)))
			{
				vec.push_back(c);
			}
		}
		vec.push_back(L']');
		return wstring(vec.begin(), vec.end());
	}
}
bool operator==(Type& left, Type& right)
{
	if (left.kind == right.kind)
	{
		if (left.name == right.name)
		{
			if (left.parameters.size() == right.parameters.size())
			{
				int32_t n = left.parameters.size();
				for (int32_t i = 0; i < n; i++)
				{
					if (left.parameters.at(i) != right.parameters.at(i))
					{
						return false;
					}
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool operator!=(Type& left, Type& right)
{
	return !(left == right);
}