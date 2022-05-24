//
// Created by fabia on 22.05.2022.
//

#include "Interpreter.h"

Interpreter::Interpreter(const std::string &fileName) {
    this->scanner = new Scanner(fileName);
    success = true;
}

Interpreter::~Interpreter() {
    delete scanner;
    delete &symTab;
}

void Interpreter::start() {
    std::cout << "Parsing started ..." << std::endl;

    muehlviertlerC();

    if (not success || symbolIsNot(Symbols::eofSy)) {
        std::cout << "There was an error in line " <<
                  scanner->getLineNumber() << " and column " <<
                  scanner->getColumnNumber() << "!";

    } else {
        std::cout << "Done.";
    }
}

void Interpreter::semError(const std::string &message) {
    std::cout << "Semantic error: " << message << " in line"
        << scanner->getLineNumber() << " and column "
        << scanner->getColumnNumber() << "." << std::endl;
}

bool Interpreter::symbolIsNot(Symbols::Symbol symbol) {
    success = (scanner->getCurrentSymbol() == symbol) && success;
    return !success;
}

void Interpreter::muehlviertlerC() {
    if (scanner->getCurrentSymbol() == Symbols::miaSy) {
        variableDec();
        if (!success) return;
        if (symbolIsNot(Symbols::periodSy)) return;
        scanner->NewSy();
    }

    statSeq();
    if (!success) return;

    ending();
}

void Interpreter::variableDec() {
    if (scanner->getCurrentSymbol() != Symbols::miaSy) {
        return;
    }
    scanner->NewSy();
    if (symbolIsNot(Symbols::habnSy)) return;
    scanner->NewSy();

    if (symbolIsNot(Symbols::identSy)) return;

    symTab.declareVariable(scanner->getIdent());

    scanner->NewSy();

    while (scanner->getCurrentSymbol() == Symbols::commaSy) {
        scanner->NewSy();
        if (symbolIsNot(Symbols::identSy)) return;

        bool declared = symTab.declareVariable(scanner->getIdent());

        if (!declared){
            std::cout << "Variable declared mutliple times" << std::endl;
        }

        scanner->NewSy();
    }
}

void Interpreter::statSeq() {
    stat();
    if (!success) return;

    while (scanner->getCurrentSymbol() == Symbols::periodSy && scanner->getCurrentSymbol() != Symbols::jezSy){
        scanner->NewSy();
        stat();
        if (!success) return;
    }
}

void Interpreter::stat() {
    switch (scanner->getCurrentSymbol()) {
        case Symbols::identSy: {
            std::string varName;
            if (!symTab.isDeclared(scanner->getIdent())) {
                semError("Variable not declared");
            } else {
                varName = scanner->getIdent();
            }

            scanner->NewSy();
            if (symbolIsNot(Symbols::assignSy)) return;
            scanner->NewSy();
            int result = expr();

            symTab.setValue(varName, result);
            break;
        }
        case Symbols::writeSy: {
            scanner->NewSy();
            Symbols::Symbol sy = scanner->getCurrentSymbol();

            if (sy == Symbols::identSy) {
                std::string ident = scanner->getIdent();
                if (not symTab.isDeclared(ident)) {
                    success = false;
                    return;
                }
                std::cout << symTab.getValue(ident) << std::endl;
                scanner->NewSy();
            } else if (sy == Symbols::leftParSy) {
                scanner->NewSy();
                int result = expr();
                if (!success) return;

                std::cout << result << std::endl;
                if (symbolIsNot(Symbols::rightParSy)) return;
                scanner->NewSy();
            } else if (sy == Symbols::singleQuoteSy) {
                std::cout << scanner->getComment() << std::endl;
                scanner->NewSy();
            }

            break;
        }
    }
}

int Interpreter::expr() {
    int result = term();
    if (!success) return -1;

    Symbols::Symbol currentSymbol = scanner->getCurrentSymbol();
    while (currentSymbol == Symbols::plusSy || currentSymbol == Symbols::minusSy) {
        switch (currentSymbol) {
            case Symbols::plusSy:
                scanner->NewSy();
                result += term();
                if (!success) return -1;
                break;
            case Symbols::minusSy:
                scanner->NewSy();
                result -= term();
                if (!success) return -1;
                break;
        }
        currentSymbol = scanner->getCurrentSymbol();
    }

    return result;
}

int Interpreter::term() {
    int result = fact();
    if (!success) return -1;

    Symbols::Symbol currentSymbol = scanner->getCurrentSymbol();
    while (currentSymbol == Symbols::timesSy || currentSymbol == Symbols::dividedSy) {
        switch (currentSymbol) {
            case Symbols::timesSy:
                scanner->NewSy();
                result *= term();
                if (!success) return -1;
                break;
            case Symbols::dividedSy:
                scanner->NewSy();
                result = int (result / term());
                if (!success) return -1;
                break;
        }
        currentSymbol = scanner->getCurrentSymbol();
    }

    return result;
}

int Interpreter::fact() {
    switch (scanner->getCurrentSymbol()) {
        case Symbols::identSy: {
            std::string ident = scanner->getIdent();
            if (!symTab.isDeclared(ident)) {
                semError("Variable not declared");
                return -1;
            } else {
                scanner->NewSy();
                return symTab.getValue(ident);
            }
        }
        case Symbols::numberSy: {
            int result = scanner->getCurrentNumber();
            scanner->NewSy();
            return result;
        }
        case Symbols::leftParSy: {

            scanner->NewSy();

            if (!success || symbolIsNot(Symbols::rightParSy)) return -1;

            scanner->NewSy();

            return expr();
        }
    }
    success = false;
    return -1;
}

void Interpreter::ending() {
    if (symbolIsNot(Symbols::jezSy)) return;
    scanner->NewSy();

    if (symbolIsNot(Symbols::heanSy)) return;
    scanner->NewSy();

    if (symbolIsNot(Symbols::maSy)) return;
    scanner->NewSy();

    if (symbolIsNot(Symbols::aufSy)) return;
    scanner->NewSy();

    if (symbolIsNot(Symbols::callSignSy)) return;
    scanner->NewSy();
}

