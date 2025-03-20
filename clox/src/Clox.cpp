#include "Clox.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <Scanner.hpp>

bool CLOX::hadError = false;

CLOX::CLOX() {}

void CLOX::run(std::string source) {
  std::cout << source << std::endl;
  Scanner scanner = Scanner(source);
  std::vector<Token> tokens = scanner.scanTokens();

  // For now, just print the tokens.
  for (Token token : tokens) {
    std::cout << token.toString() << std::endl;
  }
}


int CLOX::runFile(std::string filePath) {
  std::ifstream stream(filePath);

  if (!stream) {
    std::cerr << "Can't open input file!";
    exit(1);
  }

  std::ostringstream buffer;
  buffer << stream.rdbuf();

  run(buffer.str());

  if (hadError) {
    exit(65);
  }

  return 0;
}

void CLOX::runPrompt() {
  while (true) {
    std::cout << "> ";
    std::string prompt;

    if (!std::getline(std::cin, prompt)) {
      std::cout << "\nExiting REPL..." << std::endl;
      break;
    }

    run(prompt);
    hadError = false;
  }
}


void CLOX::error(int line, std::string message) {
  report(line, "", message);
}

void CLOX::report(int line, std::string where, std::string message) {
  std::cout << "[line " << line << "] Error" << where << ": " << message << std::endl;
  hadError = true;
}