#ifndef TYPE_CHECKER_HPP
#define TYPE_CHECKER_HPP
#include "Expression.hpp"
#include "Namespace.hpp"
#include "Scope.hpp"
#include "SymbolTable.hpp"

class TypeChecker : public Expression::Visitor
{
public:
	// NamespaceList& namespaceList;
	// Namespace& currentNamespace;
	// SymbolTable global;
	// SymbolTable* current;
	// TypeChecker(NamespaceList& namespaceList);
	NamespaceRecord& nsRecord;
	shared_ptr<Namespace> nsPtr;
	Scope* scope;
	TypeChecker(NamespaceRecord& record);

	void Check(shared_ptr<Namespace> nsPtr);
	void CheckModule(Module& moduleInfo);
	void CheckClass(Class& classInfo);
	void CheckField(Field& field);
	void CheckFunction(Function& function);
	void Collect(shared_ptr<Namespace> nsPtr);

	void Visit(ConstantExpression* node) override;
	void Visit(UnaryExpression* node) override;
	void Visit(BinaryExpression* node) override;
	void Visit(AssignExpression* node) override;
	void Visit(BlockExpression* node) override;
	void Visit(IfThenExpression* node) override;
	void Visit(IfThenElseExpression* node) override;
	// void Visit(DefVarExpression* node) override;
	// void Visit(DefFunExpression* node) override;
	// void Visit(ParameterExpression* node) override;
	void Visit(CallExpression* node) override;
	void Visit(VariableExpression* node) override;
	void Visit(ReturnExpression* node) override;
	void Visit(WhileExpression* node) override;
	// void Visit(ModuleExpression* node) override;
	// void Visit(ClassExpression* node) override;
	void Visit(DotExpression* node) override;
};
#endif // TYPE_CHECKER_HPP