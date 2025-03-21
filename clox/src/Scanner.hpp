#ifndef CLOX_SCANNER_HPP
#define CLOX_SCANNER_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <Token.hpp>

class Scanner {
private:
  const std::string source;
  std::vector<Token> tokens;
  int start;
  int current;
  int line;

  static const std::unordered_map<std::string, TokenType> keywords;

  bool isAtEnd();
  void scanToken();
  char advance();
  void addToken(TokenType);
  void addToken(TokenType, LiteralType);
  bool match(char);
  char peek();
  char peekNext();
  bool isDigit(char);
  bool isAlpha(char);
  bool isAlphaNumeric(char);

  void stringLiteral();
  void numberLiteral();
  void identifier();

public:
  Scanner(std::string);
  std::vector<Token> scanTokens();
};

#endif