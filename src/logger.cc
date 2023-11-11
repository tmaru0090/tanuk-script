#include "logger.hh"
#include <iostream>
void Logger::addLog(const std::string& name, const std::string& text,
		    LogType type) {
  auto temp = LoggerData();
  temp.text = text;
  temp.type = type;
  temp.len = text.length();
  _log[name] = temp;
}
LoggerData Logger::get(const std::string& key){
    auto ret = _log.find(key);
    if(ret != _log.end()){
      return ret->second;
    }
}

void Logger::printLogList(){
    for(auto&& val:_log){
	std::cout << "Keys: " << val.first << " Log:" << " Type: " << Logger::getLogTypeToString(val.second.type) <<"\n" <<"AllLength:" <<  val.second.len  << "\n" << "Text:" << val.second.text<< std::endl;
    }
}
void Logger::printLog(const std::string& key) {
  
}
std::string Logger::getLogText(const std::string& key) {
    auto logData = get(key);
    return logData.text;
}
LogType Logger::getLogType(const std::string& key) {
     auto logData = get(key);
     return logData.type;
}

