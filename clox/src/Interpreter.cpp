#include "Interpreter.hpp"
#include <Clox.hpp>

Interpreter::Interpreter() {
  environment = std::make_unique<Environment>();
}

LiteralType Interpreter::visitBinaryExpr(BinaryPtr expr) noexcept(false) {
  LiteralType right = evaluate(std::move(expr->right));
  LiteralType left = evaluate(std::move(expr->left));

  switch (expr->op.type) {
  case TokenType::MINUS:
    checkNumberOperands(expr->op, left, right);
    return std::get<double>(left) - std::get<double>(right);
  case TokenType::SLASH:
    checkNumberOperands(expr->op, left, right);
    return std::get<double>(left) / std::get<double>(right);
  case TokenType::STAR:
    checkNumberOperands(expr->op, left, right);
    return std::get<double>(left) * std::get<double>(right);
  case TokenType::PLUS:
    if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
      return std::get<double>(left) + std::get<double>(right);
    }

    if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right)) {
      return std::get<std::string>(left) + std::get<std::string>(right);
    }

    throw RuntimeError(expr->op, "Operands must be of type number or string.");

    break;
  case TokenType::GREATER:
    checkNumberOperands(expr->op, left, right);
    return std::get<double>(left) > std::get<double>(right);
  case TokenType::GREATER_EQUAL:
    checkNumberOperands(expr->op, left, right);
    return std::get<double>(left) >= std::get<double>(right);
  case TokenType::LESS:
    checkNumberOperands(expr->op, left, right);
    return std::get<double>(left) < std::get<double>(right);
  case TokenType::LESS_EQUAL:
    checkNumberOperands(expr->op, left, right);
    return std::get<double>(left) <= std::get<double>(right);
  case TokenType::EQUAL_EQUAL: return isEqual(left, right);
  case TokenType::BANG_EQUAL: return !isEqual(left, right);
  }

  return std::monostate{};
}

LiteralType Interpreter::visitUnaryExpr(UnaryPtr expr) {
  LiteralType right = evaluate(std::move(expr->right));

  switch (expr->op.type) {
  case TokenType::BANG:
    return !isTruthy(right);
  case TokenType::MINUS:
    checkNumberOperand(expr->op, right);
    return -std::get<double>(right);
  }

  return std::monostate{};
}

LiteralType Interpreter::visitGroupingExpr(GroupingPtr expr) {
  return evaluate(std::move(expr->expression));
}

LiteralType Interpreter::visitLiteralExpr(LiteralPtr expr) {
  return expr->value;
}

LiteralType Interpreter::visitVariableExpr(VariablePtr expr) {
  return environment->get(expr->name);
}

LiteralType Interpreter::visitAssignExpr(AssignPtr expr) {
  LiteralType value = evaluate(std::move(expr->value));
  environment->assign(expr->name, value);
  return value;
}

LiteralType Interpreter::evaluate(Expr expr) {
  return std::visit([this](auto& x) -> LiteralType {
    if constexpr (std::is_same_v<std::decay_t<decltype(x)>, BinaryPtr >) {
      return this->visitBinaryExpr(std::move(x));
    }
    else if constexpr (std::is_same_v<std::decay_t<decltype(x)>, UnaryPtr >) {
      return this->visitUnaryExpr(std::move(x));
    }
    else if constexpr (std::is_same_v<std::decay_t<decltype(x)>, GroupingPtr >) {
      return this->visitGroupingExpr(std::move(x));
    }
    else if constexpr (std::is_same_v<std::decay_t<decltype(x)>, LiteralPtr >) {
      return this->visitLiteralExpr(std::move(x));
    }
    else if constexpr (std::is_same_v<std::decay_t<decltype(x)>, VariablePtr >) {
      return this->visitVariableExpr(std::move(x));
    }
    else if constexpr (std::is_same_v<std::decay_t<decltype(x)>, AssignPtr >) {
      return this->visitAssignExpr(std::move(x));
    }

    return std::monostate{};
    }, expr);
}

void Interpreter::checkNumberOperand(Token token, LiteralType operand) noexcept(false) {
  if (std::holds_alternative<double>(operand)) return;

  throw RuntimeError(token, "Operand must be number.");
}

void Interpreter::checkNumberOperands(Token token, LiteralType left, LiteralType right) noexcept(false) {
  if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) return;

  throw RuntimeError(token, "Operands must be number.");
}

bool Interpreter::isEqual(LiteralType a, LiteralType b) {
  return std::visit([](const auto& x, const auto& y) -> bool {
    if constexpr (std::is_same_v<std::decay_t<decltype(x)>, std::decay_t<decltype(y)>>) {
      return x == y;
    }
    else {
      return false;
    }
    }, a, b);
}

bool Interpreter::isTruthy(LiteralType literal) {
  if (std::holds_alternative<std::monostate>(literal)) {
    return false;
  }

  if (std::holds_alternative<bool>(literal)) {
    return std::get<bool>(literal);
  }

  return true;
}

std::string Interpreter::stringify(LiteralType literal) {
  if (std::holds_alternative<std::monostate>(literal)) {
    return "nil";
  }

  if (std::holds_alternative<std::string>(literal)) {
    return "\"" + std::get<std::string>(literal) + "\"";
  }

  if (std::holds_alternative<bool>(literal)) {
    return std::get<bool>(literal) ? "true" : "false";
  }

  return std::to_string(std::get<double>(literal));
}

void Interpreter::interpret(std::vector<Stmt> statements) {
  try {
    for (Stmt& statement : statements) {
      execute(std::move(statement));
    }
  }
  catch (const RuntimeError& e) {
    CLOX::runtimeError(e);
  }
}

void Interpreter::visitExpressionStmt(ExpressionPtr stmt) {
  evaluate(std::move(stmt->expression));
}

void Interpreter::visitPrintStmt(PrintPtr stmt) {
  LiteralType value = evaluate(std::move(stmt->expression));
  std::cout << stringify(value) << std::endl;
}

void Interpreter::visitVarStmt(VarPtr stmt) {
  LiteralType value = std::monostate{};
  if (std::holds_alternative<std::monostate>(stmt->initializer)) {
    value = evaluate(std::move(stmt->initializer));
  }

  environment->define(stmt->name.lexeme, value);
}

void Interpreter::visitBlockStmt(BlockPtr stmt) {
  executeBlock(stmt->statements, std::make_unique<Environment>(std::move(environment)));
}

void Interpreter::execute(Stmt&& statement) {
  std::visit([this](auto& x) -> void {
    if constexpr (std::is_same_v<std::decay_t<decltype(x)>, ExpressionPtr>) {
      this->visitExpressionStmt(std::move(x));
    }
    else if constexpr (std::is_same_v<std::decay_t<decltype(x)>, PrintPtr>) {
      this->visitPrintStmt(std::move(x));
    }
    else if constexpr (std::is_same_v<std::decay_t<decltype(x)>, VarPtr>) {
      this->visitVarStmt(std::move(x));
    }
    else if constexpr (std::is_same_v<std::decay_t<decltype(x)>, BlockPtr>) {
      this->visitBlockStmt(std::move(x));
    }
    }, std::move(statement));
}

void Interpreter::executeBlock(std::vector<Stmt>& statements, std::unique_ptr<Environment> environment) {
  std::unique_ptr<Environment> previous = std::move(this->environment);
  try {
    this->environment = std::move(environment);
    for (Stmt& statement : statements) {
      execute(std::move(statement));
    }
  }
  catch (const std::exception& ex) {}

  this->environment = std::move(previous);
}
