#ifndef CLOX_RUNTIME_ERROR_HPP
#define CLOX_RUNTIME_ERROR_HPP

#include <stdexcept>
#include <Token.hpp>

class RuntimeError : public std::runtime_error {
public:
  const Token token;

  RuntimeError(Token token, const std::string& message)
    : token(token), std::runtime_error(message) {};
};

#endif