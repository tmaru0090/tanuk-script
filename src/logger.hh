/****logger.hh****/
/****Logger Class****/

#pragma once
#include <map>
#include <memory>
#include <string>

#include "ekind.hh"
#include "singleton.hh"

// ログデータを格納するための構造体
struct LoggerData {
  std::string text;
  int len;
  LogType type;
};
// シングルトンパターンを使ったログクラス
class Logger final : public Singleton<Logger> {
 public:
  friend Singleton<Logger>;
  Logger() {}
  void addLog(const std::string& key, const std::string& text, LogType type);
  void printLog(const std::string& key);
  void printLogList();
  LoggerData get(const std::string& key);
  std::string getLogText(const std::string& key);
  LogType getLogType(const std::string& key);
  static std::string getLogTypeToString(const LogType& type) {
    std::string temp = "";
    switch (type) {
      case LogType::Info:
        temp += "Info";
        break;
      case LogType::Debug:
        temp += "Debug";
        break;
      case LogType::Warning:
        temp += "Warning";
        break;
      case LogType::Error:
        temp += "Error";
        break;
      default:
        break;
    }
    return temp;
  }

 private:
  std::map<std::string, LoggerData> _log;
};
