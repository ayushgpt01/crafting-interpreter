#ifndef CLOX_STMT_HPP
#define CLOX_STMT_HPP

#include <ExprStruct.hpp>

struct Expression;
struct Print;
struct Var;
struct Block;
struct If;

using ExpressionPtr = std::unique_ptr<Expression>;
using PrintPtr = std::unique_ptr<Print>;
using VarPtr = std::unique_ptr<Var>;
using BlockPtr = std::unique_ptr<Block>;
using IfPtr = std::unique_ptr<If>;

using Stmt = std::variant<std::monostate, ExpressionPtr, PrintPtr, VarPtr, BlockPtr, IfPtr>;

struct Expression {
  Expr expression;

  explicit Expression(Expr expression) : expression(std::move(expression)) {};
};

struct Var {
  Token name;
  Expr initializer;

  Var(Token name, Expr initializer)
    : name(std::move(name)), initializer(std::move(initializer)) {
  };
};

struct Print {
  Expr expression;

  explicit Print(Expr expression) : expression(std::move(expression)) {};
};

struct Block {
  std::vector<Stmt> statements;

  explicit Block(std::vector<Stmt> statements) : statements(std::move(statements)) {};
};

struct If {
  Expr condition;
  Stmt thenBranch;
  Stmt elseBranch;

  If(Expr condition, Stmt thenBranch, Stmt elseBranch)
    : condition(std::move(condition)),
    thenBranch(std::move(thenBranch)),
    elseBranch(std::move(elseBranch)) {
  };
};

#endif