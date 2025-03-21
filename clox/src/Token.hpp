#ifndef CLOX_TOKEN_HPP
#define CLOX_TOKEN_HPP

#include <TokenType.hpp>
#include <string>
#include <variant>

using LiteralType = std::variant<std::monostate, std::string, double, bool>;

class Token {
public:
  const TokenType type;
  const std::string lexeme;
  const LiteralType literal;
  const int line;

  Token(TokenType type, std::string lexeme, LiteralType literal, int line);
  std::string toString() const;

private:
  std::string tokenTypeToString() const;
  std::string literalToString() const;
};

#endif

