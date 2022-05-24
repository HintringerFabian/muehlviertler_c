cmake_minimum_required(VERSION 3.22)
project(MVC)

set(CMAKE_CXX_STANDARD 23)

add_executable(MVC main.cpp Scanner/Scanner.cpp Scanner/Scanner.h Scanner/Symbols.h Interpreter/Interpreter.cpp Interpreter/Interpreter.h SymbolTable/SymTab.cpp SymbolTable/SymTab.h SymbolTable/VariableInfo.cpp SymbolTable/VariableInfo.h)
