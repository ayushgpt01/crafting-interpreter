#ifndef CLOX_PARSER_HPP
#define CLOX_PARSER_HPP

#include <vector>
#include <initializer_list>
#include <functional>
#include <stdexcept>
#include <optional>
#include <CLOX.hpp>
#include <ExprStruct.hpp>
#include <StmtStruct.hpp>

class Parser {
  std::vector<Token> tokens;
  int current;

  class ParseError : public std::runtime_error {
  public:
    ParseError(const std::string& message) : std::runtime_error(message) {};
  };

  Expr assignment();
  Expr expression();
  Expr equality();
  Expr comparison();
  Expr term();
  Expr factor();
  Expr unary();
  Expr primary();

  Expr resolve(std::initializer_list<TokenType>, std::function<Expr()>);
  Token consume(TokenType, std::string) noexcept(false);
  ParseError error(Token, std::string);
  void synchronize();

  bool match(std::initializer_list<TokenType>);
  bool check(TokenType);
  bool isAtEnd();
  Token advance();
  Token peek();
  Token previous();

  Stmt statement();
  Stmt printStatement();
  Stmt expressionStatement();
  std::vector<Stmt> block();

  Stmt declaration();
  Stmt varDeclaration();

public:
  std::vector<Stmt> parse();
  Parser(std::vector<Token> tokens);
};

#endif