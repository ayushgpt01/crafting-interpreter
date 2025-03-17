#ifndef TOKEN_H
#define TOKEN_H

#include <TokenType.h>
#include <string>
#include <variant>

class Token {
  const TokenType type;
  const std::string lexeme;
  const std::variant<std::monostate, std::string, double> literal;
  const int line;

public:
  Token(TokenType type, std::string lexeme, std::variant<std::monostate, std::string, double> literal, int line);
  std::string toString() const;

private:
  std::string tokenTypeToString() const;
  std::string literalToString() const;
};

#endif

