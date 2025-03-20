#ifndef EXPR_HPP
#define EXPR_HPP

#include <variant>
#include <memory>

class ExprVisitor;

class Expr {
public:
  virtual ~Expr() = default;
  virtual void accept(ExprVisitor& visitor) const = 0;
};

#endif