//
// Created by fabia on 22.05.2022.
//

#ifndef MVC_SYMTAB_H
#define MVC_SYMTAB_H


#include <string>
#include <vector>
#include "VariableInfo.h"

class SymTab {
public:
    SymTab();
    ~SymTab();

    bool declareVariable(const std::string& varName);
    bool isDeclared(const std::string& varName);

    void setValue(const std::string& varName, int value);
    int getValue(const std::string& varName);

private:
    std::vector<VariableInfo>* variables;

    bool contains(const std::string& varName);
};


#endif //MVC_SYMTAB_H
