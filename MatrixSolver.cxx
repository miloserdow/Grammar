//
// Created by milos on 12/30/17.
//

#include "MatrixSolver.h"

void MatrixSolver::solve() {
    int N = graph.size();

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (std::string label : graph[i][j])
                if (!grammar[label].empty())
                    graph[i][j].push_back(*grammar[label].begin());

    bool changed = true;
    while (changed) {
        changed = false;
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    std::vector<std::string> start = graph[i][k], finish = graph[k][j];
                    for (std::string s : start) {
                        for (std::string f : finish) {
                            std::string n = s + f;
                            if (grammar.find(n) != grammar.end()) {
                                std::vector<std::string> concat = grammar[n];
                                for (std::string elem : concat) {
                                    if (std::find(graph[i][j].begin(), graph[i][j].end(), elem) == graph[i][j].end()) {
                                        graph[i][j].push_back(elem);
                                        changed = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    std::ofstream fout(output);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!graph[i][j].empty()) {
                for (std::string str : graph[i][j]) {
                    fout << i << "," << str << "," << j << "\n";
                }
            }
        }
    }
}