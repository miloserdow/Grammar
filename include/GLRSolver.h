//
// Created by milos on 1/1/18.
//

#ifndef GRAMMAR_GLRSOLVER_H
#define GRAMMAR_GLRSOLVER_H

#include "AbstractSolver.h"

class GLRSolver : public AbstractSolver {
    bool altered;
    void dfs(int u, int v, std::string pth, int len);
public:
    GLRSolver(const grammar_t& grammar, const graph_t& graph, std::string output = "res.dat") {
        this->grammar = grammar;
        this->graph = graph;
        this->output = output;
        this->altered = false;
    }
    virtual void solve();
};


#endif //GRAMMAR_GLRSOLVER_H
