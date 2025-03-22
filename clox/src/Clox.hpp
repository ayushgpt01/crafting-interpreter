#ifndef CLOX_HPP
#define CLOX_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <Token.hpp>
#include <Scanner.hpp>
#include <Parser.hpp>
#include <AstPrinter.hpp>
#include <RuntimeError.hpp>
#include <Interpreter.hpp>
#include <StmtStruct.hpp>

class CLOX {
  static bool hadError;
  static bool hadRuntimeError;
  static Interpreter interpreter;

public:
  CLOX();
  static int runFile(std::string);
  static void runPrompt();
  static void run(std::string);
  static void error(int, std::string);
  static void error(Token, std::string);
  static void report(int, std::string, std::string);
  static void runtimeError(RuntimeError);
};

#endif