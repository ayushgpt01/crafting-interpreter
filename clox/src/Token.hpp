#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <TokenType.hpp>
#include <string>
#include <variant>

class Token {
public:
  const TokenType type;
  const std::string lexeme;
  const std::variant<std::monostate, std::string, double> literal;
  const int line;

  Token(TokenType type, std::string lexeme, std::variant<std::monostate, std::string, double> literal, int line);
  std::string toString() const;

private:
  std::string tokenTypeToString() const;
  std::string literalToString() const;
};

#endif

