#ifndef TYPE_HPP
#define TYPE_HPP
#include <string>
#include <vector>
using std::vector;
using std::wstring;
enum class TypeKind
{
	Unknown,
	Int,
	Long,
	Float,
	Double,
	Boolean,
	Char,
	String,
	Unit,
	Array,
	Function,
	Class,
	Module,
	Namespace,
	Object
};
class Type
{
public:
	TypeKind kind;
	wstring name;
	vector<Type> parameters;

	Type();
	Type(TypeKind kind, wstring name, vector<Type> parameters);

	static Type Int();
	static Type Long();
	static Type Float();
	static Type Double();
	static Type Boolean();
	static Type Char();
	static Type String();
	static Type Unit();
	static Type Array(Type elementType);
	static Type Function(vector<Type> parameters);
	static Type Module(wstring name, vector<Type> parameters);
	static Type Class(wstring name, vector<Type> parameters);
	static Type Namespace(wstring name);
	static Type Object(wstring name, vector<Type> parameters);

	bool IsInt();
	bool IsLong();
	bool IsFloat();
	bool IsDouble();
	bool IsBoolean();
	bool IsChar();
	bool IsString();
	bool IsUnit();
	bool IsArray();
	bool IsFunction();
	bool IsModule();
	bool IsClass();
	bool IsNamespace();
	bool IsObject();
};
wstring TypeToString(Type& type);
bool operator==(Type& left, Type& right);
bool operator!=(Type& left, Type& right);
#endif // TYPE_HPP