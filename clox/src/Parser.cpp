#include <Parser.hpp>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {
  current = 0;
};

Expr Parser::expression() {
  return equality();
}

Expr Parser::resolve(std::initializer_list<TokenType> tokens, std::function<Expr()> func) {
  Expr expr = func();

  while (match(tokens)) {
    Token op = previous();
    Expr right = func();
    expr = BinaryPtr(std::make_unique<Binary>(std::move(expr), op, std::move(right)));
  }

  return expr;
}

Expr Parser::equality() {
  return resolve({ TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL }, std::bind(&Parser::comparison, this));
}

Expr Parser::comparison() {
  return resolve({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL }, std::bind(&Parser::term, this));
}

Expr Parser::term() {
  return resolve({ TokenType::MINUS, TokenType::PLUS }, std::bind(&Parser::factor, this));
}

Expr Parser::factor() {
  return resolve({ TokenType::SLASH, TokenType::STAR }, std::bind(&Parser::unary, this));
}

Expr Parser::unary() {
  if (match({ TokenType::BANG, TokenType::MINUS })) {
    Token op = previous();
    Expr right = unary();
    return UnaryPtr(std::make_unique<Unary>(op, std::move(right)));
  }

  return primary();
}

Expr Parser::primary() {
  if (match({ TokenType::FALSE })) return LiteralPtr(std::make_unique<Literal>(false));
  if (match({ TokenType::TRUE })) return LiteralPtr(std::make_unique<Literal>(true));
  if (match({ TokenType::NIL })) return LiteralPtr(std::make_unique<Literal>(std::monostate{}));

  if (match({ TokenType::NUMBER, TokenType::STRING })) {
    return LiteralPtr(std::make_unique<Literal>(previous().literal));
  }

  if (match({ TokenType::LEFT_PAREN })) {
    Expr expr = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after expression");
    return GroupingPtr(std::make_unique<Grouping>(std::move(expr)));
  }

  throw error(peek(), "Expect expression.");
}

Token Parser::consume(TokenType type, std::string message) noexcept(false) {
  if (check(type)) return advance();

  throw error(peek(), message);
}

Parser::ParseError Parser::error(Token token, std::string message) {
  CLOX::error(token, message);
  return ParseError(message);
}

void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous().type == TokenType::SEMICOLON) return;

    switch (peek().type)
    {
    case TokenType::CLASS:
    case TokenType::FUN:
    case TokenType::VAR:
    case TokenType::FOR:
    case TokenType::IF:
    case TokenType::WHILE:
    case TokenType::PRINT:
    case TokenType::RETURN:
      return;
    }

    advance();
  }
}

std::optional<Expr> Parser::parse() {
  try {
    return expression();
  }
  catch (const ParseError& e) {
    return std::nullopt;
  }
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