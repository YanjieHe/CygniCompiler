#ifndef TYPE_HPP
#define TYPE_HPP
// #include <memory>
#include <string>
#include <vector>
// using std::shared_ptr;
using std::vector;
using std::wstring;
// class Type;
// class PrimitiveType;
// using TypePtr = shared_ptr<Type>;
// using PrimitiveTypePtr = shared_ptr<PrimitiveType>;
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
	Function,
	Object
};
class Type
{
public:
	TypeKind kind;
	wstring name;
	vector<Type> parameters;
	Type();
	Type(wstring name, vector<Type> parameters);
	static Type Int();
	static Type Long();
	static Type Float();
	static Type Double();
	static Type Boolean();
	static Type Char();
	static Type String();
	static Type Unit();
	static Type Function(vector<Type> parameters);

	bool IsInt();
	bool IsLong();
	bool IsFloat();
	bool IsDouble();
	bool IsBoolean();
	bool IsChar();
	bool IsString();
	bool IsUnit();
	bool IsFunction();
};
wstring TypeToString(Type& type);
bool operator==(Type& left, Type& right);
bool operator!=(Type& left, Type& right);
#endif // TYPE_HPP