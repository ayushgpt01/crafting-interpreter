#include <Parser.hpp>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {
  current = 0;
};

Expr Parser::expression() {
  return equality();
}

Expr Parser::parse(std::initializer_list<TokenType> tokens, std::function<Expr()> func) {
  Expr expr = func();

  while (match(tokens)) {
    Token op = previous();
    Expr right = func();
    expr = BinaryPtr(std::make_unique<Binary>(std::move(expr), op, std::move(right)));
  }

  return expr;
}

Expr Parser::equality() {
  return parse({ TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL }, std::bind(&Parser::comparison, this));
}

Expr Parser::comparison() {
  return parse({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL }, std::bind(&Parser::term, this));
}

bool Parser::match(std::initializer_list<TokenType> tokens) {
  for (TokenType token : tokens) {
    if (check(token)) {
      advance();
      return true;
    }
  }

  return false;
}

bool Parser::check(TokenType token) {
  if (isAtEnd()) return false;
  return peek().type == token;
}

Token Parser::advance() {
  if (!isAtEnd()) current++;
  return previous();
}

bool Parser::isAtEnd() {
  return peek().type == TokenType::_EOF;
}

Token Parser::peek() {
  return tokens.at(current);
}

Token Parser::previous() {
  return tokens.at(current - 1);
}