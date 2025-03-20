#ifndef EXPR_NODES_HPP
#define EXPR_NODES_HPP

#include <Expr.hpp>
#include <Token.hpp>

class Binary : public Expr {
public:
  const std::shared_ptr<Expr> left;
  const Token op;
  const std::shared_ptr<Expr> right;

  Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right)
    : left(left), op(op), right(right) {
  };

  void accept(ExprVisitor& visitor) const override;
};

class Grouping : public Expr {
public:
  const std::shared_ptr<Expr> expression;

  Grouping(std::shared_ptr<Expr> expression) : expression(expression) {};

  void accept(ExprVisitor& visitor) const override;
};

class Literal : public Expr {
public:
  const std::variant<std::monostate, std::string, double> value;

  Literal(std::variant<std::monostate, std::string, double> value) : value(value) {};

  void accept(ExprVisitor& visitor) const override;
};

class Unary : public Expr {
public:
  const Token op;
  const std::shared_ptr<Expr> right;

  Unary(Token op, std::shared_ptr<Expr> right) : op(op), right(right) {};

  void accept(ExprVisitor& visitor) const override;
};

#endif