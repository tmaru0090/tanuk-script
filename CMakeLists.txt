cmake_minimum_required(VERSION 3.2)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
project("tanucc_script")
set(SOURCES src/main.cc src/lexer.cc src/parser.cc src/common.cc src/symbol_mgr.cc  src/semantic_analyzer.cc src/logger.cc src/decoder.cc)
add_executable(tksc ${SOURCES})

