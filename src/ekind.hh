/****ekind.hh****/
/****Enum Lists****/
#pragma once
enum class LogType{
  Info,
  Warning,
  Debug,
  Error,
};

// ノードの種類を表す列挙型
enum class NodeType {
  Ident,	   // 識別子
  Eq,		   // =記号
  Add,		   // +記号
  Sub,		   // -記号
  Mul,		   // *記号
  Div,		   // /記号
  IntLiteral,	   // 整数リテラル
  FloatLiteral,	   // 浮動小数点リテラル
  CharLiteral,	   // 文字列リテラル ダブルクオーテーション
  CharLiteral2,	   // 文字列リテラル シングルクォーテーション
  LeftParen,	   // 左括弧
  RightParen,	   // 右括弧
  LeftHockParen,   // 左鉤括弧
  RightHockParen,  // 右鉤括弧
  LeftCurlyParen,  // 左波括弧
  RightCurlyParen,  // 右波括弧
  Semicolon,	    // ;記号
  RefSymbol,	    // &記号
  Fn,		    // fnキーワード
  Let,		    // letキーワード
  Const,	    // constキーワード
  If,		    // ifキーワード
  For,		    // forキーワード
  While,	    // whileキーワード
  Where,	    // whereキーワード
  Ref,		    // refキーワード
};

// シンボルの種類を表す列挙型
enum class SymbolType {
  Func,		     // 関数シンボル
  Variable,	     // 変数シンボル
  Object,	     // オブジェクトシンボル
  ObjectFunc,	     // オブジェクト内のメソッドシンボル
  Const,	     // 定数シンボル
  ControlStructure,  // 制御構造シンボル
};
// 変数の型を表す列挙型
enum class VariableType {
  Func,	   // 関数型
  Int,	   // 整数型
  Float,   // 浮動小数点型1
  Double,  // 浮動小数点型2
  Char,	   // 文字型
  String,  // 文字列型
};

// トークンの種類を表す列挙型
enum class TokenType {
  Ident,	   // 識別子
  Eq,		   // =記号
  Add,		   // +記号
  Sub,		   // -記号
  Mul,		   // *記号
  Div,		   // /記号
  IntLiteral,	   // 整数リテラル
  FloatLiteral,	   // 浮動小数点リテラル
  CharLiteral,	   // 文字列リテラル ダブルクオーテーション
  CharLiteral2,	   // 文字列リテラル シングルクォーテーション
  Comment,	   // コメント
  Conma,	   // コンマ
  LeftParen,	   // 左括弧
  RightParen,	   // 右括弧
  LeftHockParen,   // 左鉤括弧
  RightHockParen,  // 右鉤括弧
  LeftCurlyParen,  // 左波括弧
  RightCurlyParen,  // 右波括弧
  Semicolon,	    // ;記号
  RefSymbol,	    // &記号
  OperatorEq,	    // 比較演算子 ==記号
  Fn,		    // fnキーワード
  Let,		    // letキーワード
  Const,	    // constキーワード
  If,		    // ifキーワード
  For,		    // forキーワード
  While,	    // whileキーワード
  Where,	    // whereキーワード
  Ref,		    // refキーワード
  Return,	    // return キーワード
  Eof		    // 入力の終わり
};
// 文字エンコードの種類を表す列挙型
enum class CharCodeFormat {
  UTF8,	    // UTF-8
  UTF16,    // UTF-16
  SJIS,	    // SHIFTJIS
  JIS,	    // JIS
  UNKNOWN,  // UNKNOWN
};
// 標準出力で使える色の種類を表す列挙型
enum class PrintColors {
  Black,   // 黒
  White,   // 白
  Red,	   // 赤
  Blue,	   // 青
  Green,   // 緑
  Yellow,  // 黄色
  Purple,  // 紫
  Cyan,	   // 水色
};
// 式の優先度を表す列挙型
enum class ExprPrecedence {
  High,	 // 高い
  Low,	 // 低い
};
