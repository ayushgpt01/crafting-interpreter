#ifndef CLOX_ENVIRONMENT_HPP
#define CLOX_ENVIRONMENT_HPP

#include <memory>
#include <unordered_map>
#include <RuntimeError.hpp>

class Environment {
private:
  std::unordered_map<std::string, LiteralType> values;

public:
  std::unique_ptr<Environment> enclosing;
  LiteralType get(Token) noexcept(false);
  void assign(Token, LiteralType) noexcept(false);
  void define(std::string, LiteralType);
  Environment();
  Environment(std::unique_ptr<Environment>);

  // Delete copy constructor and assignment operator
  Environment(const Environment&) = delete;
  Environment& operator=(const Environment&) = delete;
};

#endif

