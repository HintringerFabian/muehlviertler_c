//
// Created by fabia on 22.05.2022.
//

#ifndef MVC_INTERPRETER_H
#define MVC_INTERPRETER_H


#include <vector>
#include "../Scanner/Scanner.h"
#include "../SymbolTable/VariableInfo.h"
#include "../SymbolTable/SymTab.h"

class Interpreter {
public:
    explicit Interpreter(const std::string &fileName);
    ~Interpreter();
    void start();

private:
    Scanner* scanner;
    SymTab symTab;
    bool success;

    void semError(const std::string& message);
    bool symbolIsNot(Symbols::Symbol symbol);

    void muehlviertlerC();
    void variableDec();

    // various commands
    void statSeq();
    void stat();

    // math
    int expr();
    int term();
    int fact();

    // program ending
    void ending();
};


#endif //MVC_INTERPRETER_H
