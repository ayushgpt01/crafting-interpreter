#ifndef CLOX_HPP
#define CLOX_HPP

#include <string>
#include <Token.hpp>

class CLOX {
  static bool hadError;

public:
  CLOX();
  static int runFile(std::string);
  static void runPrompt();
  static void run(std::string);
  static void error(int, std::string);
  static void error(Token, std::string);
  static void report(int, std::string, std::string);
};

#endif