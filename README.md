# Crafting Interpreters - Java, TypeScript & C++ Implementation

This repository contains my implementation of the projects from the book [Crafting Interpreters](https://craftinginterpreters.com/) by Robert Nystrom. I am following the book closely and implementing the interpreter in **Java, TypeScript, and C++** to deepen my understanding of interpreters and language design.

## Overview
The book covers two main interpreters:
1. **Tree-Walk Interpreter** (Lox) - Implemented in Java.
2. **Bytecode Virtual Machine** - Implemented in C++ (WIP).

Additionally, I am implementing a **TypeScript version** of the tree-walk interpreter to explore language differences and improve my familiarity with TypeScript for interpreter development.

## Features
- Fully functional **tree-walk interpreter** in Java.
- Work-in-progress **TypeScript implementation** of Lox.
- Work-in-progress **C++ implementation** of the bytecode virtual machine.
- Support for **variables, functions, control flow, and classes**.
- REPL mode and script execution.
- Comprehensive error handling.

## Project Structure
```
/crafting-interpreters
│── /lox      # Java implementation of Lox (Tree-Walk Interpreter)
│── /tlox     # TypeScript implementation of Lox (WIP)
│── /clox     # C++ implementation of the Bytecode VM (WIP)
│── /examples # Sample Lox scripts
│── README.md
```

## Installation & Usage

### Java (Tree-Walk Interpreter)
#### Prerequisites:
- Java 17+
- Maven (optional for building)

#### Run:
```sh
cd lox
javac com/craftinginterpreters/lox/*.java
java com.craftinginterpreters.lox.Lox
```

### TypeScript (Tree-Walk Interpreter - WIP)
#### Prerequisites:
- Node.js (latest LTS)
- TypeScript

#### Run:
```sh
cd tlox
npm install
npm run build
npm start
```

### C++ (Bytecode VM - WIP)
#### Prerequisites:
- C++ Compiler (GCC/Clang/MSVC)
- CMake

#### Build & Run:
```sh
cd clox
mkdir build && cd build
cmake ..
make
./clox
```

## Example Code
**Hello, World! in Lox**
```lox
print "Hello, world!";
```

**Factorial Function:**
```lox
fun fact(n) {
  if (n <= 1) return 1;
  return n * fact(n - 1);
}
print fact(5); // Output: 120
```

## Roadmap
- ✅ Tree-Walk Interpreter in Java
- 🔄 TypeScript Implementation (WIP)
- 🔄 Bytecode VM in C++ (WIP)
- 🔄 Optimizations and Performance Improvements

## References
- [Crafting Interpreters](https://craftinginterpreters.com/)
- [Java Implementation Guide](https://craftinginterpreters.com/contents.html)
- [TypeScript Porting Notes](#) *(To be added)*
- [C++ VM Development Notes](#) *(To be added)*

## License
This project follows the **MIT License**. Feel free to use and modify the code as needed.

---
### Contributions & Feedback
This is a personal learning project, but feedback and discussions are welcome! If you find any issues or have suggestions, feel free to open an issue or reach out.