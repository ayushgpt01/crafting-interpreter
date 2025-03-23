#include <Environment.hpp>

void Environment::define(std::string name, LiteralType value) {
  values.insert({ name, value });
}

void Environment::assign(Token token, LiteralType value) noexcept(false) {
  auto it = values.find(token.lexeme);

  if (it != values.end()) {
    values.at(token.lexeme) = value;
    return;
  }

  throw RuntimeError(token, "Undefined variable '" + token.lexeme + "'.");
}

LiteralType Environment::get(Token token) noexcept(false) {
  auto it = values.find(token.lexeme);
  if (it != values.end()) {
    return it->second;
  }

  throw RuntimeError(token, "Undefined variable '" + token.lexeme + "'.");
}
