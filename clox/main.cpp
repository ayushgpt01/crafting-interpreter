#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void run(string prompt) {
    cout << prompt << endl;
    // Scanner scanner = new Scanner(source);
    // List<Token> tokens = scanner.scanTokens();

    // // For now, just print the tokens.
    // for (Token token : tokens) {
    //   System.out.println(token);
    // }
}

int runFile(string filePath) {
    ifstream stream(filePath);

    if (!stream) {
        cerr << "Can't open input file!";
        return 1;
    }

    ostringstream buffer;
    buffer << stream.rdbuf();

    run(buffer.str());

    return 0;
}

void runPrompt() {
    while (true) {
        cout << "> ";
        string prompt;

        if (!getline(cin, prompt)) {
            cout << "\nExiting REPL..." << endl;
            break;
        }

        run(prompt);
    }
}

int main(int argc, char* argv[]) {
    vector<string> args(argv, argv + argc);
    size_t size = args.size();

    if (size > 2) {
        cout << "Usage: clox [script]";
        return 64;
    }
    else if (size == 2) {
        return runFile(args[1]);
    }
    else {
        runPrompt();
    }
}
