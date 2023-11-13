/****parser.hh****/
/****Parser Class****/
#pragma once
#include <vector>

#include "ekind.hh"
#include "struct.hh"
#include <memory>
class Parser {
 public:
  void operator() (std::vector<Token>& tokens);
  Parser() = default;
  Parser(std::vector<Token>& tokens);
  ~Parser() = default;
  // トークン分けされた文字列をASTに変換
  std::unique_ptr<Node> parse();
  // 代入文の解析
  std::unique_ptr<Node> parseAssignment();
  // 式の解析
  std::unique_ptr<Node> parseExpr();
  // 現在のリスト上のトークンを進める
  void nextVecToken();
  // 現在のトークンを取得
  Token currentToken();
  // 次のトークンを予測
  Token getPeekToken();
  // 現在のトークンの優先度を取得
  ExprPrecedence getPrecedence(TokenType type);
  // ツリー状に現在のASTを表示
  void printNodeTree(std::unique_ptr<Node> node, int depth = 0);

 private:
  std::vector<Token>& _tokens;  // 現在のトークン
  int index;			      // 現在の文字のインデックス
};

