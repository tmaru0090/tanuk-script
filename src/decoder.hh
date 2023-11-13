/****decoder.hh****/
/****Decoder Class****/
#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <memory>
#include "common.hh"
#include "define.hh"
#include "exception.hh"
#include "lexer.hh"
#include "logger.hh"
#include "parser.hh"
#include <vector>
// デコードクラス
class Decoder {
 public:
  void versionsPrint(const Token& token) {
    if (token.type == TokenType::Comment) {
      std::regex pattern(R"(\d+\.\d+)");
      std::smatch match;
      std::string versions = "";
      float version = 0.0;
      if (std::regex_search(token.value, match, pattern)) {
        versions = match[0];
      }
      try {
        version = std::stof(versions);
        std::cout << "Tanuk-Script Versions"
                  << "[" << version << "]" << std::endl;
      } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid Arugument Error:" << e.what() << std::endl;
        exit(1);
      }
    }
  }

  void decode(std::vector<Token>& tokens,std::unique_ptr<Node> node) {
      
   }
};

