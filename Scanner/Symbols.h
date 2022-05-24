//
// Created by fabia on 21.05.2022.
//

#ifndef MVC_SYMBOLS_H
#define MVC_SYMBOLS_H

class Symbols {
public:
    enum Symbol { eofSy, errorSy,
                    leftParSy, rightParSy,
                    identSy, numberSy,
                    assignSy, commaSy, periodSy,

                    // variable declaration
                    miaSy, habnSy,
                    // write to console
                    writeSy, singleQuoteSy,
                    // math operations
                    plusSy, minusSy, timesSy, dividedSy,
                    // ending of the program
                    jezSy, heanSy, maSy, aufSy, callSignSy,
                    // not yet implemented
                    readSy
    };
};

#endif //MVC_SYMBOLS_H
