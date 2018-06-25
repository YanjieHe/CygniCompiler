#include "TestType.hpp"
#include "Type.hpp"
#include <iostream>
#include <vector>
using std::endl;
using std::vector;
using std::wcout;
void TestBasicTypes()
{
	Type intType = Type::Int();
	Type arrayType(L"Array", vector<Type>{intType});
	if (TypeToString(intType) != L"Int")
	{
		wcout << L"TestBasicTypes Int fails" << endl;
	}
	if (TypeToString(arrayType) != L"Array[Int]")
	{
		wcout << L"TestBasicTypes Int fails" << endl;
	}
}