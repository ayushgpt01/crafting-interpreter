#include "ExprVisitor.hpp"

void Binary::accept(ExprVisitor& visitor) const {
  visitor.visit(*this);
}

void Literal::accept(ExprVisitor& visitor) const {
  visitor.visit(*this);
}

void Grouping::accept(ExprVisitor& visitor) const {
  visitor.visit(*this);
}

void Unary::accept(ExprVisitor& visitor) const {
  visitor.visit(*this);
}