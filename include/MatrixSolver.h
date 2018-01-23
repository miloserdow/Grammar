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
    graph_t graph;
    grammar_t grammar;
public:
    MatrixSolver(const std::string& grammarInp, const std::string& graphInp, const std::string& output = "res.dat") {
        this->grammarInp = grammarInp;
        this->graphInp = graphInp;
        this->output = output;

        readGrammarFromFile(grammarInp, grammar);
        readGraphFromFile(graphInp, graph);
    }

    void solve() override;
};


#endif //GRAMMAR_MATRIXSOLVER_H
