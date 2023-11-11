#pragma once
#include <map>
#include <stack>
#include "struct.hh"
#include <string>
class SymbolMgr {
 public:
 private:
  std::stack<std::map<std::string,Symbol>>_stack;
};
