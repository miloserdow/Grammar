//
// Created by milos on 12/30/17.
//

#ifndef GRAMMAR_ABSTRACTSOLVER_H
#define GRAMMAR_ABSTRACTSOLVER_H

#include "utils.h"

class AbstractSolver {
protected:
    std::string grammarInp;
    std::string graphInp;
    std::string output;
public:
    AbstractSolver() {}
    AbstractSolver(const std::string& grammarInp, const std::string& graphInp, const std::string& output = "res.dat") {
        this->grammarInp = grammarInp;
        this->graphInp = graphInp;
        this->output = output;
    }
    virtual void solve() = 0;
};


#endif //GRAMMAR_ABSTRACTSOLVER_H
