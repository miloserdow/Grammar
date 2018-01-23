//
// Created by milos on 12/30/17.
//

#include <cassert>
#include "MatrixSolver.h"

void MatrixSolver::solve() {
    assert(!grammar.empty() && !graph.empty() && output != "" && "invalid input params!");

    int N = graph.size();

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (const std::string &label : graph[i][j])
                if (!grammar[label].empty())
                {
                    std::vector<std::string> tmpBuf;
                    for (const auto &nonTerm : grammar[label])
                    {
                        if (std::find(tmpBuf.begin(), tmpBuf.end(), nonTerm) == tmpBuf.end())
                        {
                            tmpBuf.push_back(nonTerm);
                        }
                    }
                    graph[i][j].insert(graph[i][j].end(), tmpBuf.begin(), tmpBuf.end());
                }

    bool changed = true;
    while (changed) {
        changed = false;
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    std::vector<std::string> start = graph[i][k], finish = graph[k][j];
                    for (const std::string &s : start) {
                        for (const std::string &f : finish) {
                            std::string n = s + f;
                            for (const auto &grmRule : grammar)
                            {
                                if (grmRule.first == n)
                                {
                                    std::vector<std::string> buf;
                                    for (const auto &nonTerm : grmRule.second)
                                    {
                                        if (std::find(graph[i][j].begin(), graph[i][j].end(), nonTerm) == graph[i][j].end())
                                        {
                                            if (std::find(buf.begin(), buf.end(), nonTerm) == buf.end()) {
                                                buf.push_back(nonTerm);
                                                changed = true;
                                            }
                                        }
                                    }
                                    graph[i][j].insert(graph[i][j].end(), buf.begin(), buf.end());
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