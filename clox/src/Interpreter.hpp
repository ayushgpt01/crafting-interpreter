#ifndef CLOX_INTERPRETER_HPP
#define CLOX_INTERPRETER_HPP

#include <vector>
#include <StmtStruct.hpp>
#include <Environment.hpp>

class Interpreter {
private:
  std::unique_ptr<Environment> environment;
  LiteralType visitBinaryExpr(BinaryPtr) noexcept(false);
  LiteralType visitUnaryExpr(UnaryPtr);
  LiteralType visitGroupingExpr(GroupingPtr);
  LiteralType visitLiteralExpr(LiteralPtr);
  LiteralType visitVariableExpr(VariablePtr);
  LiteralType visitAssignExpr(AssignPtr);
  LiteralType visitLogicalExpr(LogicalPtr);

  void visitExpressionStmt(ExpressionPtr);
  void visitPrintStmt(PrintPtr);
  void visitVarStmt(VarPtr);
  void visitBlockStmt(BlockPtr);
  void visitIfStmt(IfPtr);

  LiteralType evaluate(Expr);
  void checkNumberOperand(Token, LiteralType) noexcept(false);
  void checkNumberOperands(Token, LiteralType, LiteralType) noexcept(false);

  bool isEqual(LiteralType, LiteralType);
  bool isTruthy(LiteralType);
  std::string stringify(LiteralType);
  void execute(Stmt&&);
  void executeBlock(std::vector<Stmt>&, std::unique_ptr<Environment>);

public:
  // Interprets a vector of statements, taking ownership by moving them.
  // Pass with std::move (e.g., interpret(std::move(statements))) to transfer
  // ownership of the statements vector. After this call, the original vector
  // will be empty (moved-from state). Passing without std::move will fail to
  // compile because Stmt contains non-copyable std::unique_ptrs.
  void interpret(std::vector<Stmt>);
  Interpreter();
};

#endif