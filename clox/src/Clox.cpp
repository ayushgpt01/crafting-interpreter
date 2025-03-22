#include "Clox.hpp"

bool CLOX::hadError = false;
bool CLOX::hadRuntimeError = false;
Interpreter CLOX::interpreter;

CLOX::CLOX() {}

void CLOX::run(std::string source) {
  std::cout << source << std::endl;
  Scanner scanner = Scanner(source);
  std::vector<Token> tokens = scanner.scanTokens();
  Parser parser = Parser(tokens);
  std::vector<Stmt> statements = parser.parse();

  if (hadError) return;

  interpreter.interpret(std::move(statements));
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

  if (hadError) exit(65);
  if (hadRuntimeError) exit(70);

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

void CLOX::error(Token token, std::string message) {
  if (token.type == TokenType::_EOF) {
    report(token.line, " at end", message);
  }
  else {
    report(token.line, " at '" + token.lexeme + "'", message);
  }
}

void CLOX::error(int line, std::string message) {
  report(line, "", message);
}

void CLOX::report(int line, std::string where, std::string message) {
  std::cout << "[line " << line << "] Error" << where << ": " << message << std::endl;
  hadError = true;
}

void CLOX::runtimeError(RuntimeError error) {
  std::cout << error.what() << "\n[line " << error.token.line << "]" << std::endl;
  hadRuntimeError = true;
}
