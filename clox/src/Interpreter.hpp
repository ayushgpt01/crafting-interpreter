#ifndef CLOX_INTERPRETER_HPP
#define CLOX_INTERPRETER_HPP

#include <ExprStruct.hpp>
#include <Clox.hpp>

class Interpreter {

  LiteralType visitBinaryExpr(BinaryPtr expr) noexcept(false);
  LiteralType visitUnaryExpr(UnaryPtr expr);
  LiteralType visitGroupingExpr(GroupingPtr expr);
  LiteralType visitLiteralExpr(LiteralPtr expr);

  LiteralType evaluate(Expr);
  void checkNumberOperand(Token, LiteralType) noexcept(false);
  void checkNumberOperands(Token, LiteralType, LiteralType) noexcept(false);

  bool isEqual(LiteralType, LiteralType);
  bool isTruthy(LiteralType);
  std::string stringify(LiteralType);

public:
  void interpret(Expr);
};

#endif