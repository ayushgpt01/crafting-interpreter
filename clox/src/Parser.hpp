#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <initializer_list>
#include <functional>
#include <Token.hpp>
#include <ExprStruct.hpp>

class Parser {
  std::vector<Token> tokens;
  int current;

  Expr expression();
  Expr equality();
  Expr comparison();
  Expr term();
  Expr factor();
  Expr unary();
  Expr primary();

  Expr parse(std::initializer_list<TokenType>, std::function<Expr()>);
  bool match(std::initializer_list<TokenType>);
  bool check(TokenType);
  bool isAtEnd();

  Token advance();
  Token peek();
  Token previous();

public:
  Parser(std::vector<Token> tokens);
};

#endif