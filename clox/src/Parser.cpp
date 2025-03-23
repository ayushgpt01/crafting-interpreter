#include <Parser.hpp>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {
  current = 0;
};

Expr Parser::expression() {
  return assignment();
}

Expr Parser::assignment() {
  Expr expr = equality();

  if (match({ TokenType::EQUAL })) {
    Token equals = previous();
    Expr value = assignment();

    if (std::holds_alternative<VariablePtr>(expr)) {
      Token name = std::get<VariablePtr>(expr)->name;
      return AssignPtr(std::make_unique<Assign>(Assign(name, std::move(value))));
    }

    error(equals, "Invalid assignment value.");
  }

  return expr;
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

  if (match({ TokenType::IDENTIFIER })) {
    return VariablePtr(std::make_unique<Variable>(Variable(previous())));
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

std::vector<Stmt> Parser::parse() {
  std::vector<Stmt> statements = std::vector<Stmt>();

  while (!isAtEnd()) {
    statements.push_back(declaration());
  }

  return statements;
}

Stmt Parser::declaration() {
  try {
    if (match({ TokenType::VAR })) return varDeclaration();

    return statement();
  }
  catch (const ParseError& error) {
    synchronize();
    return std::monostate{};
  }
}

Stmt Parser::varDeclaration() {
  Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");

  Expr initializer = std::monostate{};
  if (match({ TokenType::EQUAL })) {
    initializer = expression();
  }

  consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
  return VarPtr(std::make_unique<Var>(Var(name, std::move(initializer))));
}

Stmt Parser::statement() {
  if (match({ TokenType::PRINT })) return printStatement();
  if (match({ TokenType::LEFT_BRACE })) return BlockPtr(std::make_unique<Block>(Block(std::move(block()))));

  return expressionStatement();
}



Stmt Parser::printStatement() {
  Expr expr = expression();
  consume(TokenType::SEMICOLON, "Expect ';' after value.");

  return PrintPtr(std::make_unique<Print>(Print(std::move(expr))));
}

Stmt Parser::expressionStatement() {
  Expr expr = expression();
  consume(TokenType::SEMICOLON, "Expect ';' after expression.");

  return ExpressionPtr(std::make_unique<Expression>(Expression(std::move(expr))));
}

std::vector<Stmt> Parser::block() {
  std::vector<Stmt> statements = std::vector<Stmt>();

  while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
    statements.push_back(declaration());
  }

  consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
  return statements;
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