#!/usr/bin/env node
import * as fs from "fs";
import * as readline from "readline";
import Scanner from "./Classes/Scanner";
import Token from "./Classes/Token";

let hadError: boolean = false;

const reader = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const askQuestion = (query: string): Promise<string> => {
  return new Promise((resolve) => reader.question(query, resolve));
};

const readFileAsString = (filePath: string): string => {
  try {
    // Synchronously read the file contents
    const content = fs.readFileSync(filePath, "utf-8");
    return content;
  } catch (er) {
    const error = er as Error;
    console.error("Error reading file:", error.message);
    process.exit(1); // Exit with an error code
  }
};

function run(source: string) {
  const scanner = new Scanner(source);
  const tokens: Token[] = scanner.scanTokens();

  for (let token of tokens) {
    console.log(token);
  }
}

function runFile(path: string) {
  const file = readFileAsString(path);
  run(file);

  if (hadError) {
    process.exit(65);
  }
}

async function runPrompt() {
  console.log("Starting REPL for tlox - ");
  while (true) {
    const line = await askQuestion("> ");
    if (!line || line === "exit") break;
    run(line);
    hadError = false;
  }
}

export function error(line: number, message: string) {
  report(line, "", message);
}

function report(line: number, where: string, message: string) {
  console.log("[line " + line + "] Error" + where + ": " + message);
  hadError = true;
}

function main() {
  const args = process.argv.slice(2);

  if (args.length >= 2) {
    console.log("Usage: tlox [script]");
    process.exit(64);
  } else if (args.length == 1) {
    runFile(args[0]);
  } else {
    runPrompt();
  }

  process.exit(0);
}

main();
