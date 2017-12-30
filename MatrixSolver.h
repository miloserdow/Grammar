//
// Created by milos on 12/30/17.
//

#ifndef GRAMMAR_MATRIXSOLVER_H
#define GRAMMAR_MATRIXSOLVER_H

#include <algorithm>
#include <fstream>
#include "utils.h"
#include "AbstractSolver.h"

class MatrixSolver : public AbstractSolver {
public:
    MatrixSolver(const grammar_t& grammar, const graph_t& graph, std::string output = "res.dat") {
        this->grammar = grammar;
        this->graph = graph;
        this->output = output;
    }
    virtual void solve();
};


#endif //GRAMMAR_MATRIXSOLVER_H
