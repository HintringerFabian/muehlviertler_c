//
// Created by fabia on 22.05.2022.
//

#include "VariableInfo.h"

VariableInfo::VariableInfo(const std::string& varName, int value) {
    this->name = varName;
    this->value = value;
}

VariableInfo::~VariableInfo() = default;

std::string VariableInfo::getName() {
    return name;
}

void VariableInfo::setValue(int newValue) {
    this->value = newValue;
}

int VariableInfo::getValue() const {
    return value;
}
