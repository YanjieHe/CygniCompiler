#ifndef MODULE_HPP
#define MODULE_HPP
#include "Expression.hpp"
#include <string>
using std::string;
class Module
{
public:
	string path;
	ExpPtr tree;
	Module(string path, ExpPtr tree);
};
#endif // MODULE_HPP