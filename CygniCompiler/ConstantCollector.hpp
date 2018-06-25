#ifndef CONSTANT_COLLECTOR_HPP
#define CONSTANT_COLLECTOR_HPP
#include "Expression.hpp"
#include "SymbolTable.hpp"
#include <any>
using std::any;

class ConstantCollector : public Expression::Visitor
{
public:
	SymbolTable table;
	unordered_map<wstring, int> stringTable;
	ConstantCollector();
	void Visit(ConstantExpression* node) override;
	void Visit(UnaryExpression* node) override;
	void Visit(BinaryExpression* node) override;
	void Visit(AssignExpression* node) override;
	void Visit(BlockExpression* node) override;
	void Visit(IfThenExpression* node) override;
	void Visit(IfThenElseExpression* node) override;
	void Visit(DefVarExpression* node) override;
	void Visit(DefFunExpression* node) override;
	void Visit(ParameterExpression* node) override;
	void Visit(CallExpression* node) override;
	void Visit(VariableExpression* node) override;
	void Visit(ReturnExpression* node) override;
	void Visit(WhileExpression* node) override;
};
#endif // CONSTANT_COLLECTOR_HPP