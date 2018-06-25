#include "Type.hpp"
Type::Type()
	: kind{TypeKind::Unknown}
	, name{L"Unknown"}
{
}
Type::Type(wstring name, vector<Type> parameters)
	: name{name}
	, parameters(parameters)
{
	if (name == L"Int")
	{
		kind = TypeKind::Int;
	}
	else if (name == L"Long")
	{
		kind = TypeKind::Long;
	}
	else if (name == L"Float")
	{
		kind = TypeKind::Float;
	}
	else if (name == L"Double")
	{
		kind = TypeKind::Double;
	}
	else if (name == L"Boolean")
	{
		kind = TypeKind::Boolean;
	}
	else if (name == L"Char")
	{
		kind = TypeKind::Char;
	}
	else if (name == L"String")
	{
		kind = TypeKind::Long;
	}
	else if (name == L"Unit")
	{
		kind = TypeKind::Unit;
	}
	else if (name == L"Function")
	{
		kind = TypeKind::Function;
	}
	else
	{
		kind = TypeKind::Object;
	}
}
Type Type::Int()
{
	static Type type = Type(L"Int", vector<Type>());
	return type;
}
Type Type::Long()
{
	static Type type = Type(L"Long", vector<Type>());
	return type;
}
Type Type::Float()
{
	static Type type = Type(L"Float", vector<Type>());
	return type;
}
Type Type::Double()
{
	static Type type = Type(L"Double", vector<Type>());
	return type;
}
Type Type::Boolean()
{
	static Type type = Type(L"Boolean", vector<Type>());
	return type;
}
Type Type::Char()
{
	static Type type = Type(L"Char", vector<Type>());
	return type;
}
Type Type::String()
{
	static Type type = Type(L"String", vector<Type>());
	return type;
}
Type Type::Unit()
{
	static Type type = Type(L"Unit", vector<Type>());
	return type;
}
Type Type::Function(vector<Type> parameters)
{
	return Type(L"Function", parameters);
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
bool Type::IsFunction()
{
	return kind == TypeKind::Function;
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
		for (int i = 1, n = type.parameters.size(); i < n; i++)
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
				int n = left.parameters.size();
				for (int i = 0; i < n; i++)
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