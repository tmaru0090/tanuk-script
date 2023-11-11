/****lexer.hh****/
/****Lexer Class****/

#pragma once
#include <string>
#include <vector>

#include "struct.hh"
// 字句解析器を表すクラス
class Lexer {
 public:
  // コンストラクタ
  Lexer(const std::string& input);
  void operator()(const std::string& input);
  // 現在の文字列を取得
  char currentChar();
  // 現在の文字列を進める
  void nextChar();
  // 空白や改行を読み飛ばす
  void skipWhiteSpace();
  // コメントを読み込む (//記号)
  Token readComment();
  // コメントを読み込む2 (/**/記号)
  Token readComment2();
  // 識別子やキーワードを読み込む
  Token readIdent();
  // 整数リテラルを読み込む
  Token readIntLiteral();
  // 文字列リテラルを読み込む (ダブルクオーテーション)
  Token readCharLiteral();
  // 文字列リテラルを読み込む2 (シングルクオーテーション)
  Token readCharLiteral2();

  // 文字列リテラルを読み込むヘルパー関数 (ダブルクオーテーション)
  std::string readCharLiteralHelper();
  // 文字列リテラルを読み込むヘルパー関数 (シングルクオーテーション)
  std::string readCharLiteralHelper2();

  // 文字列が終端か調べる
  bool isEof();
  // 次のトークンを返す
  Token nextToken();
  // 入力文字列をトークン列に変換する
  std::vector<Token> tokenize();
  // トークンを種類別に表示する
  void printLexerData(const std::vector<Token>& tokens);

 private:
  std::string input;  // 入力文字列
  int index;          // 現在の文字のインデックス
  int line;           // 現在の行番号
  int column;         // 現在の列番号
};

