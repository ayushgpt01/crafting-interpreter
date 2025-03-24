#ifndef CLOX_EXPR_STRUCT_HPP
#define CLOX_EXPR_STRUCT_HPP

#include <variant>
#include <memory>
#include <Token.hpp>

struct Binary;
struct Grouping;
struct Literal;
struct Unary;
struct Variable;
struct Assign;
struct Logical;

using BinaryPtr = std::unique_ptr<Binary>;
using GroupingPtr = std::unique_ptr<Grouping>;
using LiteralPtr = std::unique_ptr<Literal>;
using UnaryPtr = std::unique_ptr<Unary>;
using VariablePtr = std::unique_ptr<Variable>;
using AssignPtr = std::unique_ptr<Assign>;
using LogicalPtr = std::unique_ptr<Logical>;

using Expr = std::variant<std::monostate, BinaryPtr, GroupingPtr, LiteralPtr, UnaryPtr, VariablePtr, AssignPtr, LogicalPtr>;

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

struct Variable {
  Token name;

  explicit Variable(Token name)
    : name(std::move(name)) {
  }
};

struct Assign {
  Token name;
  Expr value;

  Assign(Token name, Expr value)
    : name(std::move(name)), value(std::move(value)) {
  }
};

struct Logical {
  Expr left;
  Token op;
  Expr right;

  Logical(Expr left, Token op, Expr right)
    : left(std::move(left)), op(std::move(op)), right(std::move(right)) {
  };
};

#endif