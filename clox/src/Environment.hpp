#ifndef CLOX_ENVIRONMENT_HPP
#define CLOX_ENVIRONMENT_HPP

#include <unordered_map>
#include <RuntimeError.hpp>

class Environment {
private:
  std::unordered_map<std::string, LiteralType> values;

public:
  LiteralType get(Token) noexcept(false);
  void assign(Token, LiteralType) noexcept(false);
  void define(std::string, LiteralType);
  Environment() {};
};

#endif

