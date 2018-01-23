//
// Created by milos on 1/1/18.
//

#include <iostream>
#include <fstream>

#include "GLRSolver.h"

inline bool inDFA(const automaton_t &automation, int i, int j, const std::string &symbol) {
    for (auto &rule : automation)
        if (std::get<0>(rule) == i && std::get<1>(rule) == j && std::get<2>(rule) == symbol)
            return true;
    return false;
};

void GLRSolver::solve() {
    automaton_t edges = automaton;
    for (auto &states : startStates) {
        for (auto &nTerm : states.second) {
            auto iter = finalStates.find(nTerm);
            for (auto &final : (*iter).second)
                if (states.first == final)
                    for (int i = 0; i < statesInAutomaton; ++ i)
                        automaton.emplace_back(std::make_tuple(i, i, nTerm));
        }
    }

    for (;;) {
        bool changed = false;
        do {
            changed = false;
            int sDFA = 0, sGrm = 0, fDFA = 0, fGrm = 0;
            for (auto &edge : edges) {
                sDFA = std::get<0>(edge), fDFA = std::get<1>(edge);
                for (int i = 0; i < size; ++ i) {
                    if (sDFA == idxArr[i].first) {
                        sGrm = idxArr[i].second;
                        for (int j = 0; j < size; ++j) {
                            if (fDFA == idxArr[j].first) {
                                fGrm = idxArr[j].second;
                                for (auto &grmRule : RFA) {
                                    if (std::get<0>(grmRule) == sGrm && std::get<1>(grmRule) == fGrm) {
                                        if (std::get<2>(grmRule) == std::get<2>(edge)) {
                                            if (!matrix[i][j]) {
                                                changed = true;
                                                matrix[i][j] = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } while (changed);

        for (int k = 0; k < size; ++ k) {
            std::vector<bool> &matrixK = matrix[k];
            for (int i = 0; i < size; ++ i) {
                std::vector<bool> &matrixI = matrix[i];
                if (matrixI[k]) {
                    for (int j = 0; j < size; ++j) {
                        if (matrixK[j]) {
                            matrixI[j] = true;
                        }
                    }
                }
            }
        }

        bool needCont = false;
        edges = std::vector<std::tuple<int, int, const std::string> > (0);
        for (int i = 0; i < size; ++ i) {
            int startPos = idxArr[i].second;
            auto nonTerms = startStates.find(startPos);
            if (nonTerms != startStates.end()) {
                for (auto &nonTerminal : (*nonTerms).second) {
                    auto finalPositions = (*finalStates.find(nonTerminal)).second;
                    for (auto finalPos : finalPositions) {
                        for (int j = 0; j < size; ++j) {
                            if (matrix[i][j] && idxArr[j].second == finalPos) {
                                int sDFA = idxArr[i].first, fDFA = idxArr[j].first;
                                if (!inDFA(automaton, sDFA, fDFA, nonTerminal)) {
                                    automaton.emplace_back(std::make_tuple(sDFA, fDFA, nonTerminal));
                                    edges.emplace_back(std::make_tuple(sDFA, fDFA, nonTerminal));
                                    needCont = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (!needCont)
            break;
    }

    std::ofstream fout(output, std::ofstream::out);
    for (auto &r : automaton) {
        auto c = std::get<2>(r);
        if ((c.length() != 1 && c != "eps") || (!islower(c[0]) && ! isdigit(c[0]) && isalpha(c[0])))
             fout << std::get<0>(r) << "," << c << "," << std::get<1>(r) << std::endl;
    }
    fout.close();
}