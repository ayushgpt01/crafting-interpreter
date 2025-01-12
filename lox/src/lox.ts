#!/usr/bin/env node
import * as fs from "fs";
import * as readline from "readline";

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
  // TODO - Create Scan tokens function
  const tokens = source.split(" ");

  for (let token of tokens) {
    console.log(token);
  }
}

function runFile(path: string) {
  const file = readFileAsString(path);
  run(file);
}

async function runPrompt() {
  console.log("Starting REPL for tlox - ");
  while (true) {
    const line = await askQuestion("> ");
    if (!line || line === "exit") break;
    run(line);
  }
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
