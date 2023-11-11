
#include "parser.hh"

#include <iostream>
#include <string>

#include "common.hh"


void Parser::operator() (std::vector<Token>& tokens){
  this->_tokens = tokens;
}
Parser::Parser(std::vector<Token>& tokens) : _tokens(tokens), index(0) {}
Node* Parser::parse() {
    return parseAssignment();
}

Node* Parser::parseExpr() {
    
}
Node* Parser::parseAssignment() {
  int assignmentCount = 0;
  Node* root = nullptr;	 // ルートノード

   if(currentToken().type != TokenType::Eof) {
    if (currentToken().type == TokenType::Let) {
      auto letNode = new Node(NodeType::Let, nullptr, nullptr);	 // "let" ノード
      nextVecToken();
      auto nextToken = currentToken();
      if (currentToken().type == TokenType::Ident) {
	auto identNode =
	    new Node(NodeType::Ident, nullptr, nullptr);  // 変数名ノード
	letNode->left = identNode;  // "let" ノードと変数名ノードを接続

	// 同様に、Eq、IntLiteralノードを生成して接続

	nextVecToken();
	if (currentToken().type == TokenType::Eq) {
	  auto eqNode = new Node(NodeType::Eq, nullptr, nullptr);  // "=" ノード
	  identNode->right = eqNode;  // 変数名ノードと "=" ノードを接続

	  // 同様に、IntLiteralノードを生成して接続

	  nextVecToken();
    if (currentToken().type == TokenType::IntLiteral) {
	    auto intLiteralNode =
		new Node(NodeType::IntLiteral, nullptr, nullptr);
	    eqNode->right =
		intLiteralNode;	 // "=" ノードと IntLiteral ノードを接続

	    nextVecToken();
	    if (currentToken().type == TokenType::Semicolon) {
	      assignmentCount++;
	    }
	  }
	}
	// ルートノードに "let" ノードを接続
	if (!root) {
	  root = letNode;
	} else {
	  // 既にルートノードがある場合、"let"
	  // ノードを既存のルートノードの右側に接続
	  Node* temp = root;
	  while (temp->right) {
	    temp = temp->right;
	  }
	  temp->right = letNode;
	}
      }
 }
  }
    if (assignmentCount > 0) {
      std::cout << "代入処理が " << assignmentCount << " 回見つかりました"
		<< std::endl;
    }

    return root;  // ルートノードを返す
  }
  void Parser::nextVecToken() {
      // 現在のトークンを進める
      index++;
  }
  Token Parser::currentToken() { return _tokens[index]; }
  void Parser::printNodeTree(Node * node, int depth) {
    if (node == nullptr) {
      return;
    }

    // ツリーの階層を表現
    for (int i = 0; i < depth; i++) {
      std::cout << "  ";
    }

    // ノードの情報を表示
    std::cout << colorToPrintString("Type: ", PrintColors::Yellow)
	      << node->nodeTypeToString(node->type) << std::endl;

    // 左右のサブツリーを再帰的に表示
    if (node->left != nullptr) {
      std::cout << colorToPrintString("Left: ", PrintColors::Blue) << std::endl;
      printNodeTree(node->left, depth + 1);
    }
    if (node->right != nullptr) {
      std::cout << colorToPrintString("Right: ", PrintColors::Blue)
		<< std::endl;
      printNodeTree(node->right, depth + 1);
    }
  }

