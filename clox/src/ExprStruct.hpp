#ifndef EXPR_STRUCT_HPP
#define EXPR_STRUCT_HPP

#include <variant>
#include <memory>
#include <Token.hpp>

struct Binary;
struct Grouping;
struct Literal;
struct Unary;

using BinaryPtr = std::unique_ptr<Binary>;
using GroupingPtr = std::unique_ptr<Grouping>;
using LiteralPtr = std::unique_ptr<Literal>;
using UnaryPtr = std::unique_ptr<Unary>;

using Expr = std::variant<BinaryPtr, GroupingPtr, LiteralPtr, UnaryPtr>;

struct ExprVisitor {
  virtual void visit(const Binary& expr) = 0;
  virtual void visit(const Literal& expr) = 0;
  virtual void visit(const Unary& expr) = 0;
  virtual void visit(const Grouping& expr) = 0;
};

struct Binary {
  Expr left;
  Token op;
  Expr right;

  Binary(Expr left, Token op, Expr right)
    : left(std::move(left)), op(std::move(op)), right(std::move(right)) {
  }
};

struct Unary {
  Token op;
  Expr right;

  Unary(Token op, Expr right)
    : op(std::move(op)), right(std::move(right)) {
  }
};

struct Grouping {
  Expr expression;

  explicit Grouping(Expr expression)
    : expression(std::move(expression)) {
  }
};

struct Literal {
  std::variant<std::monostate, std::string, double> value;

  explicit Literal(std::variant<std::monostate, std::string, double> value)
    : value(std::move(value)) {
  }
};

template <typename Visitor>
void visitExpr(const Expr& expr, Visitor&& visitor) {
  std::visit(visitor, expr);
}

#endif