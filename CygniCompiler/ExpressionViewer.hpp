#ifndef EXPRESSION_VIEWER_HPP
#define EXPRESSION_VIEWER_HPP
#include "Expression.hpp"

class ExpressionViewer : public Expression::Visitor
{
public:
	ExpressionViewer();
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
#endif // EXPRESSION_VIEWER_HPP