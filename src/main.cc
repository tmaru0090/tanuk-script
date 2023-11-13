#include <fstream>
#include <iostream>
#include <string>
#include "decoder.hh" 
#define DEBUG

// メイン関数
int main(int argc, char** argv) {
 #ifndef DEBUG
  if (argc < 2) {
    std::cerr << "ファイル名が必要です" << std::endl;
    std::cerr << "Usege: tksc [Filename] [Options]" << std::endl;
    return -1;
  }

  // コマンドライン引数からファイル名を受け取る
  std::ifstream inputFile(argv[1]);

  // もしファイルが存在しないなら
  if (!inputFile.is_open()) {
    std::cout << "ファイルを読み取ることができません" << std::endl;
    return -1;
  }
  // スクリプトを一度に読み込む
  std::string input((std::istreambuf_iterator<char>(inputFile)),
		    (std::istreambuf_iterator<char>()));
  inputFile.close();
  #endif 
  #ifdef DEBUG 
  std::string input = "let a = 1000;\nlet b = 190 = 12121;\n"
		      "" ;
  #endif
  try {
    // 字句解析
    Lexer lexer(input);
    auto tokens = lexer.tokenize();
    // 構文解析や意味解析
    Parser parser(tokens);
    auto node = parser.parse();
    lexer.printLexerData(tokens);
    parser.printNodeTree(std::move(node));
    // 実行
    Decoder dec;
    dec.decode(tokens,std::move(node));
    // 下記エラー処理
  } catch (LexerException& e) {
    std::cerr << e.what() << std::endl;
  } catch (ParserException& e) {
    std::cerr << e.what() << std::endl;
  } catch (DecoderException& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

