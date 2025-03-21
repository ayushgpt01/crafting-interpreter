#include <Scanner.hpp>
#include <Clox.hpp>

const std::unordered_map<std::string, TokenType> Scanner::keywords = {
  {"and",TokenType::AND},
  {"class",TokenType::CLASS},
  {"else",TokenType::ELSE},
  {"false",TokenType::FALSE},
  {"fun",TokenType::FUN},
  {"for",TokenType::FOR},
  {"if",TokenType::IF},
  {"nil",TokenType::NIL},
  {"or",TokenType::OR},
  {"print",TokenType::PRINT},
  {"return",TokenType::RETURN},
  {"super",TokenType::SUPER},
  {"this",TokenType::THIS},
  {"true",TokenType::TRUE},
  {"var",TokenType::VAR},
  {"while",TokenType::WHILE},
};

Scanner::Scanner(std::string source) : source(source) {
  start = 0;
  current = 0;
  line = 1;
}

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  Token token = Token(TokenType::_EOF, "", std::monostate{}, line);
  tokens.push_back(token);

  return tokens;
}

bool Scanner::isAtEnd() {
  return current >= source.length();
}

void Scanner::scanToken() {
  char c = advance();

  switch (c) {
  case '(': addToken(TokenType::LEFT_PAREN); break;
  case ')': addToken(TokenType::RIGHT_PAREN); break;
  case '{': addToken(TokenType::LEFT_BRACE); break;
  case '}': addToken(TokenType::RIGHT_BRACE); break;
  case ',': addToken(TokenType::COMMA); break;
  case '.': addToken(TokenType::DOT); break;
  case '-': addToken(TokenType::MINUS); break;
  case '+': addToken(TokenType::PLUS); break;
  case ';': addToken(TokenType::SEMICOLON); break;
  case '*': addToken(TokenType::STAR); break;
  case '!':
    addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    break;
  case '=':
    addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
    break;
  case '<':
    addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
    break;
  case '>':
    addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
    break;
  case '/':
    if (match('/')) {
      while (peek() != '\n' && !isAtEnd()) advance();
    }
    else {
      addToken(TokenType::SLASH);
    }
    break;

  case ' ': case '\r': case '\t': break;
  case '\n': line++; break;
  case '"': stringLiteral(); break;

  default:
    if (isDigit(c)) {
      numberLiteral();
      break;
    }
    else if (isAlpha(c)) {
      identifier();
      break;
    }

    CLOX::error(line, "Unexpected character.");
    break;
  }
}

char Scanner::advance() {
  return source.at(current++);
}

void Scanner::addToken(TokenType type) {
  addToken(type, std::monostate{});
}

void Scanner::addToken(TokenType type, LiteralType literal) {
  std::string text = source.substr(start, current - start);
  tokens.push_back(Token(type, text, literal, line));
}

bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  if (source.at(current) != expected) return false;

  current++;
  return true;
}

char Scanner::peek() {
  if (isAtEnd()) return '\0';
  return source.at(current);
}

char Scanner::peekNext() {
  if (current + 1 >= source.length())  return '\0';
  return source.at(current + 1);
}

bool Scanner::isDigit(char c) {
  return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
  return isAlpha(c) || isDigit(c);
}

void Scanner::stringLiteral() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') line++;
    advance();
  }

  if (isAtEnd()) {
    CLOX::error(line, "Unterminated string.");
    return;
  }

  advance(); // Consume closing "

  std::string value = source.substr(start + 1, current - start - 2);
  addToken(TokenType::STRING, value);
}

void Scanner::numberLiteral() {
  while (isDigit(peek())) advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();

    while (isDigit(peek())) advance();
  }

  addToken(TokenType::NUMBER, std::stod(source.substr(start, current - start)));
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek())) advance();

  std::string text = source.substr(start, current - start);

  auto it = keywords.find(text);

  if (it != keywords.end()) {
    TokenType type = it->second;
    addToken(type);
    return;
  }

  addToken(TokenType::IDENTIFIER);
}
