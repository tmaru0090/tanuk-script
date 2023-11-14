
#include "parser.hh"

#include <exception>
#include <iostream>
#include <string>

#include "common.hh"

void Parser::operator()(std::vector<Token>& tokens) { this->_tokens = tokens; }
Parser::Parser(std::vector<Token>& tokens) : _tokens(tokens), index(0) {}
std::unique_ptr<Node> Parser::parse() {
  // スクリプト全体の基底ノードを作成
  auto node = std::make_unique<Node>(NodeType::Root, nullptr, nullptr);
  // トークンの終わりになるまでノードを生成
  while (currentToken().type != TokenType::Eof) {
    // コメントの場合はトークンを飛ばす
    if (currentToken().type == TokenType::Comment) {
      nextVecToken();
    }
    if (currentToken().type == TokenType::Let) {
      if (!node->right) {
	node->right = parseAssignment();
      } else {
	std::unique_ptr<Node> current = std::move(node->right);
	while (current->right != nullptr) {
	  current = std::move(current->right);
	}
	current->right = parseAssignment();
      }
    }
    nextVecToken();
  }
  return node;
}

std::unique_ptr<Node> Parser::parseExpr() {}

std::unique_ptr<Node> Parser::parseAssignment() {
  int assignmentCount = 0;
  auto root =
      std::make_unique<Node>(NodeType::Let, nullptr, nullptr);	// ルートノード

  if (currentToken().type == TokenType::Let) {
    auto letNode = std::make_unique<Node>(NodeType::Let, nullptr,
					  nullptr);  // "let" ノード
    nextVecToken();
    if (currentToken().type == TokenType::Ident) {
      auto identNode = std::make_unique<Node>(NodeType::Ident, nullptr,
					      nullptr);	 // 変数名ノード
      letNode->left = std::move(identNode);  // "let" ノードと変数名ノードを接続
      // 同様に、Eq、IntLiteralノードを生成して接続
      nextVecToken();
      if (currentToken().type == TokenType::Eq) {
	auto eqNode = std::make_unique<Node>(NodeType::Eq, nullptr,
					     nullptr);	// "=" ノード
	letNode->left->right =
	    std::move(eqNode);	// 変数名ノードと "=" ノードを接続

	// 同様に、IntLiteralノードを生成して接続

	nextVecToken();
	if (currentToken().type == TokenType::IntLiteral) {
	  auto intLiteralNode =
	      std::make_unique<Node>(NodeType::IntLiteral, nullptr, nullptr);
	  letNode->left->right->right = std::move(
	      intLiteralNode);	// "=" ノードと IntLiteral ノードを接続

	  nextVecToken();
	  if (currentToken().type == TokenType::Semicolon) {
	    assignmentCount++;
	  }
	}
      }
      // ルートノードに "let" ノードを接続
      if (root->left == nullptr) {
	root->left = std::move(letNode);
      } else {
	// 既にルートノードがある場合、"let"
	// ノードを既存のルートノードの右側に接続
	auto current = root->left.get();
	while (current->right) {
	  current = current->right.get();
	}
	current->right = std::move(letNode);
      }
    }
  }

  if (assignmentCount > 0) {
    std::cout << "代入処理が " << assignmentCount << " 回見つかりました"
	      << std::endl;
  }

  return root;	// ルートノードを返す
}

void Parser::nextVecToken() {
  // 現在のトークンを進める
  index++;
}
Token Parser::currentToken() { return _tokens[index]; }
void Parser::printNodeTree(std::unique_ptr<Node> node, int depth) {
  if (node == nullptr) {
    return;
  }

  // ツリーの階層を表現
  for (int i = 0; i < depth; i++) {
    std::cout << "  ";
  }

  // ノードの情報を表示
  std::cout << colorToPrintString("Parser Results:", PrintColors::Red)
	    << std::endl;
  std::cout << colorToPrintString("Type: ", PrintColors::Yellow)
	    << node->nodeTypeToString(node->type) << std::endl;

  // 左右のサブツリーを再帰的に表示
  if (node->left != nullptr) {
    std::cout << colorToPrintString("Left: ", PrintColors::Blue) << std::endl;
    printNodeTree(std::move(node->left), depth + 1);
  }
  if (node->right != nullptr) {
    std::cout << colorToPrintString("Right: ", PrintColors::Blue) << std::endl;
    printNodeTree(std::move(node->right), depth + 1);
  }
}

