#include <iostream>

#include "Scanner/Scanner.h"
#include "Interpreter/Interpreter.h"

int main() {
    std::string fileName = "../test.txt";

    Interpreter interpreter = Interpreter(fileName);
    interpreter.start();

}

