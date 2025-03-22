#ifndef CLOX_INTERPRETER_HPP
#define CLOX_INTERPRETER_HPP

#include <vector>
#include <StmtStruct.hpp>

class Interpreter {
  LiteralType visitBinaryExpr(BinaryPtr expr) noexcept(false);
  LiteralType visitUnaryExpr(UnaryPtr expr);
  LiteralType visitGroupingExpr(GroupingPtr expr);
  LiteralType visitLiteralExpr(LiteralPtr expr);
  void visitExpressionStmt(ExpressionPtr expr);
  void visitPrintStmt(PrintPtr expr);

  LiteralType evaluate(Expr);
  void checkNumberOperand(Token, LiteralType) noexcept(false);
  void checkNumberOperands(Token, LiteralType, LiteralType) noexcept(false);

  bool isEqual(LiteralType, LiteralType);
  bool isTruthy(LiteralType);
  std::string stringify(LiteralType);
  void execute(Stmt&&);

public:
  // Interprets a vector of statements, taking ownership by moving them.
  // Pass with std::move (e.g., interpret(std::move(statements))) to transfer
  // ownership of the statements vector. After this call, the original vector
  // will be empty (moved-from state). Passing without std::move will fail to
  // compile because Stmt contains non-copyable std::unique_ptrs.
  void interpret(std::vector<Stmt>);
};

#endif