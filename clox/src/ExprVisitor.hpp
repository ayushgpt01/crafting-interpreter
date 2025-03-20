#ifndef EXPR_VISITOR_HPP
#define EXPR_VISITOR_HPP

#include <ExprNodes.hpp>

class ExprVisitor {
public:
  virtual void visit(const Binary& expr) = 0;
  virtual void visit(const Literal& expr) = 0;
  virtual void visit(const Unary& expr) = 0;
  virtual void visit(const Grouping& expr) = 0;
};

#endif