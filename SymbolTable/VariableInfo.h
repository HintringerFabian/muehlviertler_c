//
// Created by fabia on 22.05.2022.
//

#ifndef MVC_VARIABLEINFO_H
#define MVC_VARIABLEINFO_H

#include <string>

class VariableInfo {
public:
    VariableInfo(const std::string& varName, int value);
    ~VariableInfo();

    std::string getName();
    void setValue(int value);
    [[nodiscard]] int getValue() const;

private:
    std::string name;
    int value;
};

#endif //MVC_VARIABLEINFO_H
