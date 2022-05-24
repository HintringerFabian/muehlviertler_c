//
// Created by fabia on 21.05.2022.
//

#include <filesystem>
#include "Scanner.h"
#include "iostream"

Scanner::Scanner(const std::string& fileName) {

    inputFile.open(fileName);

    line = "";
    charColumnNumber = 0;
    charLineNumber = 0;
    NewChar();
    NewSy();
}

Scanner::~Scanner() {
    if (inputFile.is_open()) {
        inputFile.close();
    }
}

void Scanner::NewSy() {
    while (currChar == spaceChar or
            currChar == tabChar or
            charLineNumber == 1) {
        NewChar();
    }

    lineNumber = charLineNumber;
    columnNumber = charColumnNumber;

    switch (currChar) {
        case char(0):
            assignSy(Symbols::eofSy);
            break;

        case '+':
            assignSyNewChar(Symbols::plusSy);
            break;

        case '-':
            assignSyNewChar(Symbols::minusSy);
            break;

        case '*':
            assignSyNewChar(Symbols::timesSy);
            break;

        case '/':
            assignSyNewChar(Symbols::dividedSy);
            break;

        case '(':
            assignSyNewChar(Symbols::leftParSy);
            break;

        case ')':
            assignSyNewChar(Symbols::rightParSy);
            break;

        case ',':
            assignSyNewChar(Symbols::commaSy);
            break;

        case '.':
            assignSyNewChar(Symbols::periodSy);
            break;

        case '\'':
            assignSyNewChar(Symbols::singleQuoteSy);
            break;

        case '!':
            assignSyNewChar(Symbols::callSignSy);
            break;

        case '0' ... '9':
            assignSy(Symbols::numberSy);
            numberVal = 0;

            while ((currChar >= '0') && (currChar <= '9')) {
                numberVal *= 10;
                numberVal += (int) currChar - (int) '0';
                NewChar();
            }
            break;

        case 'a' ... 'z':
        case 'A'... 'Z':
            identString = "";
            while ((currChar >= 'a' && currChar <= 'z') ||
                    (currChar >= 'A') && (currChar <= 'Z') ||
                    (currChar >= '0') && (currChar <= '9') ||
                    (currChar == '_')
                    ) {
                identString += currChar;
                NewChar();
            }
            for (char &c: identString) c = toupper(c);

            if (identString == "SCHREIB" || identString == "SCHPEIB") {
                assignSy(Symbols::writeSy);

            } else if (identString == "MIA") {
                assignSy(Symbols::miaSy);

            } else if (identString == "HABN" ||
                        identString == "NEHMAN") {
                assignSy(Symbols::habnSy);

            } else if (identString == "IS") {
                assignSy(Symbols::assignSy);

            } else if (identString == "JEZ") {
                assignSy(Symbols::jezSy);

            } else if (identString == "HEAN") {
                assignSy(Symbols::heanSy);

            } else if (identString == "MA") {
                assignSy(Symbols::maSy);

            } else if (identString == "AUF") {
                assignSy(Symbols::aufSy);

            } else if (identString == "!") {
                assignSy(Symbols::callSignSy);

            } else {
                assignSy(Symbols::identSy);
            }
            break;

        default:
            assignSy(Symbols::errorSy);
            break;
    }
}

Symbols::Symbol Scanner::getCurrentSymbol() {
    return currSy;
}


int Scanner::getCurrentNumber() const {
    return numberVal;
}

std::string Scanner::getIdent() {
    return identString;
}

int Scanner::getLineNumber() const {
    return lineNumber;
}

int Scanner::getColumnNumber() const {
    return columnNumber;
}

std::string Scanner::getComment() {
    std::string result;

    while (charColumnNumber < line.length() && currChar != '\'') {
        result += currChar;
        updateCurrCharInLine();
    }

    NewChar();

    return result;
}

void Scanner::NewChar() {
    if (charColumnNumber < line.length()) {
        updateCurrCharInLine();

    } else {
        if (!inputFile.eof()) {
            std::getline(inputFile, line);
            charLineNumber++;
            charColumnNumber = 0;
            currChar = spaceChar;

        } else {
            inputFile.close();
            currChar = eofChar;
        }
    }
}

void Scanner::updateCurrCharInLine() {
    charColumnNumber++;
    currChar = line[charColumnNumber - 1];
}

void Scanner::assignSy(Symbols::Symbol symbol) {
    currSy = symbol;
}

void Scanner::assignSyNewChar(Symbols::Symbol symbol) {
    assignSy(symbol);
    NewChar();
}
