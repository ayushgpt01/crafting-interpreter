#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <Clox.hpp>

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);
    size_t size = args.size();

    if (size > 2) {
        std::cout << "Usage: clox [script]";
        exit(64);
    }
    else if (size == 2) {
        return CLOX::runFile(args[1]);
    }
    else {
        CLOX::runPrompt();
    }
}
