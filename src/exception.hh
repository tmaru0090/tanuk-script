#pragma once 
#include <exception>
#include <string>

// スクリプト用例外基底クラス
class TanukException : public std::exception {
 public:
  TanukException(const std::string& message) : _message(message) {}
  const char* what() const noexcept override { return _message.c_str(); }
 private:
  std::string _message;
};
// レキサーの例外クラス
class LexerException : public TanukException {
 public:
  LexerException(const std::string& message) : TanukException(message) {}
 private:
};
// パーサーの例外クラス
class ParserException: public TanukException{
 public:
  ParserException(const std::string& message) : TanukException(message) {}
 private:
};
// デコーダーの例外クラス
class DecoderException: public TanukException{
 public:
  DecoderException(const std::string& message) : TanukException(message) {}
 private:
};

