//
// Created by milos on 12/30/17.
//

#ifndef GRAMMAR_ABSTRACTSOLVER_H
#define GRAMMAR_ABSTRACTSOLVER_H

#include "utils.h"

class AbstractSolver {
protected:
    grammar_t grammar;
    graph_t graph;
    std::string output;
public:
    AbstractSolver() {}
    AbstractSolver(const grammar_t& grammar, const graph_t& graph, std::string output = "res.dat") {
        this->grammar = grammar;
        this->graph = graph;
        this->output = output;
    }
    virtual void solve() = 0;
};


#endif //GRAMMAR_ABSTRACTSOLVER_H
