#include <Environment.hpp>
#include <iostream>

void Environment::define(std::string name, LiteralType value) {
  values.insert({ name, value });
}

Environment::Environment() : enclosing(nullptr) {};
Environment::Environment(std::unique_ptr<Environment> enclosing)
  : enclosing(std::move(enclosing)) {
};

void Environment::assign(Token token, LiteralType value) noexcept(false) {
  auto it = values.find(token.lexeme);

  if (it != values.end()) {
    values.at(token.lexeme) = value;
    return;
  }

  if (enclosing) {
    enclosing->assign(token, value);
    return;
  }

  throw RuntimeError(token, "Undefined variable '" + token.lexeme + "'.");
}

LiteralType Environment::get(Token token) noexcept(false) {
  auto it = values.find(token.lexeme);
  if (it != values.end()) {
    return it->second;
  }

  if (enclosing) return enclosing->get(token);

  throw RuntimeError(token, "Undefined variable '" + token.lexeme + "'.");
}
