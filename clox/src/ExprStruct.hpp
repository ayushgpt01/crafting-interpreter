#ifndef EXPR_STRUCT_HPP
#define EXPR_STRUCT_HPP

#include <variant>
#include <memory>
#include <Token.hpp>

struct Binary;
struct Grouping;
struct Literal;
struct Unary;

using Expr = std::variant<std::monostate, Binary, Grouping, Literal, Unary>;

struct ExprVisitor {
  virtual void visit(const Binary& expr) = 0;
  virtual void visit(const Literal& expr) = 0;
  virtual void visit(const Unary& expr) = 0;
  virtual void visit(const Grouping& expr) = 0;
};

struct Binary {
  const Expr left;
  const Token op;
  const Expr right;

  Binary(Expr left, Token op, Expr right)
    : left(std::move(left)), op(op), right(std::move(right)) {
  }
};

struct Unary {
  const Token op;
  const Expr right;

  Unary(Token op, Expr right)
    : op(op), right(std::move(right)) {
  }
};

struct Grouping {
  const Expr expression;

  explicit Grouping(Expr expression)
    : expression(std::move(expression)) {
  }
};

struct Literal {
  const std::variant<std::monostate, std::string, double> value;

  explicit Literal(std::variant<std::monostate, std::string, double> value)
    : value(std::move(value)) {
  }
};

template <typename Visitor>
void visitExpr(const Expr& expr, Visitor&& visitor) {
  std::visit(visitor, expr);
}

#endif