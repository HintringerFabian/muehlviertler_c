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
            currSy = Symbols::eofSy;
            break;

        case '+':
            currSy = Symbols::plusSy;
            NewChar();
            break;

        case '-':
            currSy = Symbols::minusSy;
            NewChar();
            break;

        case '*':
            currSy = Symbols::timesSy;
            NewChar();
            break;

        case '/':
            currSy = Symbols::dividedSy;
            NewChar();
            break;

        case '(':
            currSy = Symbols::leftParSy;
            NewChar();
            break;

        case ')':
            currSy = Symbols::rightParSy;
            NewChar();
            break;

        case ',':
            currSy = Symbols::commaSy;
            NewChar();
            break;

        case '.':
            currSy = Symbols::periodSy;
            NewChar();
            break;

        case '\'':
            currSy = Symbols::singleQuoteSy;
            NewChar();
            break;

        case '!':
            currSy = Symbols::callSignSy;
            NewChar();
            break;

        case '0' ... '9':
            currSy = Symbols::numberSy;
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
                currSy = Symbols::writeSy;
            } else if (identString == "MIA") {
                currSy = Symbols::miaSy;
            } else if (identString == "HABN" ||
                        identString == "NEHMAN") {
                currSy = Symbols::habnSy;
            } else if (identString == "IS") {
                currSy = Symbols::assignSy;
            } else if (identString == "JEZ") {
                currSy = Symbols::jezSy;
            } else if (identString == "HEAN") {
                currSy = Symbols::heanSy;
            } else if (identString == "MA") {
                currSy = Symbols::maSy;
            } else if (identString == "AUF") {
                currSy = Symbols::aufSy;
            } else if (identString == "!") {
                currSy = Symbols::callSignSy;
            } else {
                currSy = Symbols::identSy;
            }
            break;

        default:
            currSy = Symbols::errorSy;
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
