import { TokenType, LiteralType } from "../Constants/tokenType";

class Token {
  type: TokenType;
  lexeme: string;
  literal: LiteralType;
  line: number;

  constructor(
    type: TokenType,
    lexeme: string,
    literal: LiteralType,
    line: number
  ) {
    this.type = type;
    this.lexeme = lexeme;
    this.literal = literal;
    this.line = line;
  }

  toString() {
    return this.type + " " + this.lexeme + " " + this.literal;
  }
}

export default Token;
