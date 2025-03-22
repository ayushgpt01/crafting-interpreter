#ifndef CLOX_STMT_HPP
#define CLOX_STMT_HPP

#include <ExprStruct.hpp>

struct Expression;
struct Print;

using ExpressionPtr = std::unique_ptr<Expression>;
using PrintPtr = std::unique_ptr<Print>;

using Stmt = std::variant<ExpressionPtr, PrintPtr>;

struct Expression {
  Expr expression;

  explicit Expression(Expr expression) : expression(std::move(expression)) {};
};

struct Print {
  Expr expression;

  explicit Print(Expr expression) : expression(std::move(expression)) {};
};

#endif