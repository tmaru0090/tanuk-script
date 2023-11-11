#pragma once
#include <string>
#include <vector>

#include "ekind.hh"

// トークンを表す構造体
struct Token {
  TokenType type;     // トークンの種類
  std::string value;  // トークンの値（文字列）
  int line;	      // トークンの行番号
  int column;	      // トークンの列番号

  // コンストラクタ
  Token(TokenType type, std::string value, int line, int column) {
    this->type = type;
    this->value = value;
    this->line = line;
    this->column = column;
  }
  std::string tokenTypeToString(const TokenType& type) {
    std::string temp = "";
    switch (type) {
      case TokenType::Let:
	temp += "Let";
	break;
      case TokenType::Fn:
	temp += "Fn";
	break;
      case TokenType::Eq:
	temp += "Eq";
	break;
      case TokenType::Ident:
	temp += "Ident";
	break;
      case TokenType::Semicolon:
	temp += "Semicolon";
	break;
      case TokenType::IntLiteral:
	temp += "IntLiteral";
	break;
      case TokenType::CharLiteral:
	temp += "CharLiteral";
	break;
      case TokenType::CharLiteral2:
	temp += "CharLiteral2";
	break;
      case TokenType::Add:
	temp += "Add";
	break;
      case TokenType::Sub:
	temp += "Sub";
	break;
      case TokenType::Mul:
	temp += "Mul";
	break;
      case TokenType::Div:
	temp += "Div";
	break;
      case TokenType::Comment:
	temp += "Comment";
	break;
      case TokenType::Conma:
	temp += "Conma";
	break;
      case TokenType::Const:
	temp += "Const";
	break;
      case TokenType::LeftParen:
	temp += "LeftParen";
	break;
      case TokenType::RightParen:
	temp += "RightParen";
	break;

      case TokenType::LeftHockParen:
	temp += "LeftHockParen";
	break;
      case TokenType::RightHockParen:
	temp += "RightHockParen";
	break;
      case TokenType::LeftCurlyParen:
	temp += "LeftCurlyParen";
	break;
      case TokenType::RightCurlyParen:
	temp += "RightCurlyParen";
	break;
      case TokenType::RefSymbol:
	temp += "RefSymbol";
	break;

      case TokenType::Eof:
	temp += "Eof";
	break;
      case TokenType::If:
	temp += "If";
	break;
      case TokenType::For:
	temp += "For";
	break;
      case TokenType::While:
	temp += "While";
	break;
      case TokenType::Where:
	temp += "Where";
	break;
      case TokenType::Ref:
	temp += "Ref";
	break;
      case TokenType::OperatorEq:
	temp += "OperatorEq";
	break;
      default:
	temp += "Error";
	break;
    }
    return temp;
  }
};
// ノードを表す構造体
struct Node {
  NodeType type;  // ノードの種類
  Node* left;	  // 左ノード
  Node* right;	  // 右ノード
  Node(NodeType type, Node* left, Node* right) {
    this->type = type;
    this->left = left;
    this->right = right;
  }
  std::string nodeTypeToString(const NodeType& type) {
    std::string temp = "";
    switch (type) {
      case NodeType::Let:
	temp += "Let";
	break;
      case NodeType::Fn:
	temp += "Func";
	break;
      case NodeType::Eq:
	temp += "Eq";
	break;
      case NodeType::Ident:
	temp += "Ident";
	break;
      case NodeType::IntLiteral:
	temp += "IntLiteral";
	break;
      case NodeType::CharLiteral:
	temp += "CharLiteral";
	break;
      case NodeType::CharLiteral2:
	temp += "CharLiteral2";
	break;
      case NodeType::Add:
	temp += "Add";
	break;
      case NodeType::Sub:
	temp += "Sub";
	break;
      case NodeType::Mul:
	temp += "Mul";
	break;
      case NodeType::Div:
	temp += "Div";
	break;
      case NodeType::Const:
	temp += "Const";
	break;

      default:
	temp += "Error";
	break;
    }
    return temp;
  }
};
// 関数の引数を表す構造体
struct Argument {
  int argumentNum;
  VariableType variableType;
};
// シンボルを表す構造体
struct Symbol {
  std::string name, value;
  int line, column;
  SymbolType symbolType;
  VariableType variableType;
  std::vector<Argument> arguments;
};

