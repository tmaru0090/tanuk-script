#include "common.hh"
std::string charCodeFormatToString(const CharCodeFormat& format) {
  std::string temp = "";
  switch (format) {
    case CharCodeFormat::UTF8:
      temp += "UTF8";
      break;
    case CharCodeFormat::SJIS:
      temp += "SJIS";
      break;
    case CharCodeFormat::UNKNOWN:
      temp += "UNKNOWN";
      break;
  }
  return temp;
}

CharCodeFormat getToCharCodeFormat(const std::string& string) {
  // 文字列が空ならUNKNOWNを返す
  if (string.empty()) return CharCodeFormat::UNKNOWN;

  // 文字列の先頭から2バイトを取得する
  unsigned char first = static_cast<unsigned char>(string[0]);
  unsigned char second = static_cast<unsigned char>(string[1]);

  // SJISかどうか判定する
  if ((first >= 0x81 && first <= 0x9f) || (first >= 0xe0 && first <= 0xfc)) {
    // 第一水準漢字か第二水準漢字か判定する
    if ((second >= 0x40 && second <= 0x7e) ||
	(second >= 0x80 && second <= 0xfc)) {
      return CharCodeFormat::SJIS;
    }
  }

  // UTF-8かどうか判定する
  if (first >= 0xc2 && first <= 0xf4) {
    // バイト数を取得する
    int bytes = 0;
    if (first < 0xe0)
      bytes = 2;
    else if (first < 0xf0)
      bytes = 3;
    else
      bytes = 4;

    // 残りのバイトが10xxxxxxであるか判定する
    bool is_utf8 = true;
    for (int i = 1; i < bytes; i++) {
      unsigned char next = static_cast<unsigned char>(string[i]);
      if (next < 0x80 || next > 0xbf) {
	is_utf8 = false;
	break;
      }
    }
    if (is_utf8) return CharCodeFormat::UTF8;
  }

  // 上記の条件に当てはまらなければUNKNOWNを返す
  return CharCodeFormat::UNKNOWN;
}

std::string colorToPrintString(const std::string& string, PrintColors color) {
  std::string colors_left;
  std::string colors_end = "\033[0m";
  switch (color) {
    case PrintColors::Black:
      colors_left = "\033[30m";
      break;
    case PrintColors::White:
      colors_left = "\033[37m";
      break;
    case PrintColors::Red:
      colors_left = "\033[31m";
      break;
    case PrintColors::Blue:
      colors_left = "\033[34m";
      break;
    case PrintColors::Green:
      colors_left = "\033[32m";
      break;
    case PrintColors::Yellow:
      colors_left = "\033[33m";
      break;
    case PrintColors::Purple:
      colors_left = "\033[35m";
      break;
    case PrintColors::Cyan:
      colors_left = "\033[36m";
      break;
    default:
      break;
  }

  return colors_left + string + colors_end;
}

