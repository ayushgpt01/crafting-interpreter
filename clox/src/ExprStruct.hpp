#ifndef CLOX_EXPR_STRUCT_HPP
#define CLOX_EXPR_STRUCT_HPP

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
  LiteralType value;

  explicit Literal(LiteralType value)
    : value(std::move(value)) {
  }
};

#endif