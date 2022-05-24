//
// Created by fabia on 21.05.2022.
//

#ifndef MVC_SCANNER_H
#define MVC_SCANNER_H

#include <fstream>
#include <iostream>

#include "Symbols.h"

class Scanner {
public:

    explicit Scanner(const std::string& fileName);
    ~Scanner();

    void NewSy();
    Symbols::Symbol getCurrentSymbol();

    int getCurrentNumber() const;
    std::string getIdent();
    int getLineNumber() const;
    int getColumnNumber() const;
    std::string getComment();

private:
    Symbols::Symbol currSy{};
    std::ifstream inputFile;
    std::string line;
    char currChar{};
    int charLineNumber, charColumnNumber;
    int numberVal{};
    std::string identString;
    int lineNumber{}, columnNumber{};

    const char eofChar = char(0);
    const char spaceChar = char(32);
    const char tabChar = char(9);

    void NewChar();
    void updateCurrCharInLine();
};


#endif //MVC_SCANNER_H
