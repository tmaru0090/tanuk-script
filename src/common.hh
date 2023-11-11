#pragma once 
#include <string>
#include "ekind.hh"

std::string charCodeFormatToString(const CharCodeFormat& format);
CharCodeFormat getToCharCodeFormat(const std::string& string);
std::string colorToPrintString(const std::string& string, PrintColors color);
