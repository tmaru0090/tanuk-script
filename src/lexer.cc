#include "lexer.hh"

#include <iostream>

#include "common.hh"
#include "ekind.hh"
#include "exception.hh"
// オペレーター()
void Lexer::operator()(const std::string& input){
    this->input = input;
}
// コンストラクタ
Lexer::Lexer(const std::string& input) {
  this->input = input;
  this->index = 0;
  this->line = 1;
  this->column = 1;
}

// 現在の文字を返すメソッド
char Lexer::Lexer::currentChar() { return input[index]; }

// 次の文字に進むメソッド
void Lexer::nextChar() {
  index++;
  column++;
  if (currentChar() == '\n') {
    line++;
    column = 1;
  }
}

// 空白や改行を読み飛ばすメソッド
void Lexer::skipWhiteSpace() {
  while (currentChar() == ' ' || currentChar() == '\n' ||
	 currentChar() == '\t') {
	  nextChar();
  }
}
// コメントを読み込むメソッド
Token Lexer::readComment() {
  std::string value = "";
  int start_line = line;
  int start_column = column;
  // 改行文字が現れるまでループ
  while (currentChar() != '\n') {
    value += currentChar();
    nextChar();
  }
  return Token(TokenType::Comment, value, start_line, start_column);
}
// コメントを読み込むメソッド
Token Lexer::readComment2() {
  std::string value = "";
  int start_line = line;
  int start_column = column;
  // 改行文字が現れるまでループ
  while (currentChar() != '\n') {
    value += currentChar();
    nextChar();
  }
  if (value.find("*/") == std::string::npos ||
      value.find("\n*/") == std::string::npos) {
    std::cout << "Unclosed Comment" << std::endl;
    exit(1);
  } else {
    std::cout << "Closed Comment ! Yes!" << std::endl;
  }
  return Token(TokenType::Comment, value, start_line, start_column);
}
// 識別子やキーワードを読み込むメソッド
Token Lexer::readIdent() {
  std::string value = "";
  int start_line = line;
  int start_column = column;
  while (isalpha(currentChar()) || isdigit(currentChar()) ||
	 currentChar() == '_') {
    value += currentChar();
    nextChar();
  }
  TokenType type;
  if (value == "let") {
    type = TokenType::Let;
  } else if (value == "fn") {
    type = TokenType::Fn;
  } else if (value == "const") {
    type = TokenType::Const;
  } else if (value == "where") {
    type = TokenType::Where;
  } else if (value == "if") {
    type = TokenType::If;
  } else if (value == "for") {
    type = TokenType::For;
  } else if (value == "while") {
    type = TokenType::While;
  } else if (value == "ref") {
    type = TokenType::Ref;
  } else if (value == "return") {
    type = TokenType::Return;
  } else {
    type = TokenType::Ident;
  }
  return Token(type, value, start_line, start_column);
}

// 整数リテラルを読み込むメソッド
Token Lexer::readIntLiteral() {
  std::string value = "";
  int start_line = line;
  int start_column = column;
  while (isdigit(currentChar())) {
    value += currentChar();
    nextChar();
  }
  return Token(TokenType::IntLiteral, value, start_line, start_column);
}
bool Lexer::isEof() {
  return index >= input.size();
}
Token Lexer::readCharLiteral() {
  std::string value = "";
  int start_line = line;
  int start_column = column;

  // まず最初のダブルクォートを読み込む
  if (currentChar() == '"') {
    nextChar();
    value = readCharLiteralHelper();
  } else {
    // ダブルクォートで始まっていない場合、エラーとして終了
    std::cerr << "Invalid character literal" << std::endl;
    exit(1);
  }

  return Token(TokenType::CharLiteral, value, start_line, start_column);
}

// 文字列リテラルを読み込むヘルパー関数
std::string Lexer::readCharLiteralHelper() {
  std::string value = "";

  while (!isEof() && currentChar() != '"') {
    // エスケープ文字を処理
    if (currentChar() == '\\') {
      nextChar();  // バックスラッシュをスキップ
      if (isEof()) {
	// エスケープ文字の後に文字がない場合、エラーとして終了
	std::cerr << "Unexpected end of input in character literal"
		  << std::endl;
	exit(1);
      }
      value += currentChar();  // エスケープされた文字を追加
    } else {
      value += currentChar();  // 通常の文字を追加
    }

    nextChar();
  }

  // ダブルクォートが閉じられていない場合、エラーとして終了
  if (isEof()) {
    throw LexerException("Unclosed charliteral");
  }

  // ダブルクォートを読み込んでリテラルを閉じる
  nextChar();

  return value;
}
Token Lexer::readCharLiteral2() {
  std::string value = "";
  int start_line = line;
  int start_column = column;

  // まず最初のシングルクォートを読み込む
  if (currentChar() == '\'') {
    nextChar();
    value = readCharLiteralHelper2();
  } else {
    // ダブルクォートで始まっていない場合、エラーとして終了
    std::cerr << "Invalid character literal" << std::endl;
    exit(1);
  }

  return Token(TokenType::CharLiteral2, value, start_line, start_column);
}

// 文字列リテラルを読み込むヘルパー関数
std::string Lexer::readCharLiteralHelper2() {
  std::string value = "";

  while (!isEof() && currentChar() != '\'') {
    // エスケープ文字を処理
    if (currentChar() == '\\') {
      nextChar();  // バックスラッシュをスキップ
      if (isEof()) {
	// エスケープ文字の後に文字がない場合、エラーとして終了
	std::cerr << "Unexpected end of input in character literal"
		  << std::endl;
	exit(1);
      }
      value += currentChar();  // エスケープされた文字を追加
    } else {
      value += currentChar();  // 通常の文字を追加
    }
    nextChar();
  }

  // シングルクォートが閉じられていない場合、エラーとして終了
  if (isEof()) {
    std::cerr << "Unclosed character literal" << std::endl;
    exit(1);
  }

  // ダブルクォートを読み込んでリテラルを閉じる
  nextChar();

  return value;
}

// 次のトークンを返すメソッド
Token Lexer::nextToken() {
  skipWhiteSpace();
  char c = currentChar();
  if (isEof()) {
    return Token(TokenType::Eof, "", line, column);
  } else if (isalpha(c) || c == '_') {
    return readIdent();
  } else if (isdigit(c)) {
    return readIntLiteral();
  } else if (c == '"') {
    return readCharLiteral();
  } else if (c == '\'') {
    return readCharLiteral2();
  } else if (c == '=') {
    nextChar();
    if (currentChar() == '=') {
      nextChar();
      return Token(TokenType::OperatorEq, "==", line, column);
    }
    return Token(TokenType::Eq, "=", line, column);
  } else if (c == '+') {
    nextChar();
    return Token(TokenType::Add, "+", line, column);
  } else if (c == '-') {
    nextChar();
    return Token(TokenType::Sub, "-", line, column);
  } else if (c == '*') {
    nextChar();
    return Token(TokenType::Mul, "*", line, column);
  } else if (c == '/') {
    nextChar();
    char next = currentChar();
    if (next == '/') {
      nextChar();
      return readComment();
    } else {
      nextChar();
      return Token(TokenType::Div, "/", line, column);
    }
  } else if (c == '(') {
    nextChar();
    return Token(TokenType::LeftParen, "(", line, column);
  } else if (c == ')') {
    nextChar();
    return Token(TokenType::RightParen, ")", line, column);
  } else if (c == '[') {
    nextChar();
    return Token(TokenType::LeftHockParen, "[", line, column);
  } else if (c == ']') {
    nextChar();
    return Token(TokenType::RightHockParen, "]", line, column);
  } else if (c == '{') {
    nextChar();
    if (c == '\n') {
      nextChar();
    }
    return Token(TokenType::LeftCurlyParen, "{", line, column);
  } else if (c == '}') {
    nextChar();
    return Token(TokenType::RightCurlyParen, "}", line, column);
  } else if (c == '&') {
    nextChar();
    return Token(TokenType::RefSymbol, "&", line, column);
  } else if (c == ';') {
    nextChar();
    return Token(TokenType::Semicolon, ";", line, column);
  } else if (c == ',') {
    nextChar();
    return Token(TokenType::Conma, ",", line, column);
  } else {
    std::string what = "Invlid charctor: "+std::string(1,c)+" line: "+std::to_string(line)+" column: "+std::to_string(column);
    throw LexerException(what);
    exit(1);
  }
}

// 入力文字列をトークン列に変換するメソッド
std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  Token token = nextToken();
  while (token.type != TokenType::Eof) {
    tokens.push_back(token);
    token = nextToken();
  }
  return tokens;
}
void Lexer::printLexerData(const std::vector<Token>& tokens) {
  std::cout << colorToPrintString("Lexer Results:", PrintColors::Red)
	    << std::endl;
  for (Token token : tokens) {
    std::cout << colorToPrintString(token.tokenTypeToString(token.type),
				    PrintColors::Yellow)
	      << " (" << colorToPrintString(token.value, PrintColors::Blue)
	      << ") "
	      << " ["
	      << colorToPrintString(std::to_string(token.line),
				    PrintColors::Green)
	      << ", "
	      << colorToPrintString(std::to_string(token.column),
				    PrintColors::Green)
	      << "]" << std::endl;
  }
}

