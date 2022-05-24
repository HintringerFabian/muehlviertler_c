//
// Created by fabia on 22.05.2022.
//

#include "SymTab.h"

SymTab::SymTab() {
    variables = new std::vector<VariableInfo>();
}

SymTab::~SymTab() {
    delete variables;
}

bool SymTab::declareVariable(const std::string& varName) {
    bool variableNotDeclared = !contains(varName);

    if (variableNotDeclared) {
        VariableInfo newInfo = VariableInfo(varName, 0);
        variables->push_back(newInfo);
    }
    return variableNotDeclared;
}

bool SymTab::isDeclared(const std::string& varName) {
    return contains(varName);
}

void SymTab::setValue(const std::string& varName, int value) {
    for (auto& v : *variables) {
        if (v.getName() == varName) {
            v.setValue(value);
            return;
        }
    }
}

int SymTab::getValue(const std::string& varName) {
    for (auto& v : *variables) {
        if (v.getName() == varName) {
            return v.getValue();
        }
    }
}

bool SymTab::contains(const std::string& varName) {
    for (auto& v: *variables) {
        if (v.getName() == varName) {
            return true;
        }
    }
    return false;
}
