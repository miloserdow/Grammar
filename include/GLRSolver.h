//
// Created by milos on 1/1/18.
//

#ifndef GLRSOLVER_H
#define GLRSOLVER_H


#include <string>
#include <map>
#include <vector>
#include "utils.h"
#include "AbstractSolver.h"

class GLRSolver : public AbstractSolver {
    int statesInAutomaton;
    int statesInRFA;
    int size;

    matrix_t matrix;
    automaton_t automaton;
    automaton_t RFA;
    start_states_t startStates;
    final_states_t finalStates;
    idx_arr_t idxArr;

public:
    GLRSolver(const std::string &inp, const std::string &automationInput, const std::string& x) {
        statesInRFA = 0;
        statesInAutomaton = 0;
        readRfa(inp, RFA, statesInRFA, startStates, finalStates);
        readAutomaton(automationInput, automaton, statesInAutomaton);
        size = statesInRFA * statesInAutomaton;
        matrix = matrix_t(size, std::vector<bool>(size, false));
        for (int i = 0; i < statesInAutomaton; ++ i)
            for (int j = 0; j < statesInRFA; ++ j)
                idxArr.emplace_back(std::make_pair(i, j));
        output = x;
    }

    void solve() override;
};


#endif //GLRSOLVER_H
