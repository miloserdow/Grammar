//
// Created by milos on 1/1/18.
//

#include <cassert>
#include <algorithm>
#include "GLRSolver.h"

using namespace std;

void GLRSolver::dfs(int u, int v, string currPath, int len) {
    if (grammar.find(currPath) != grammar.end()) {
        vector<string> nonterms = grammar[currPath];
        for (string nonterm : nonterms) {
            if (find(graph[v][u].begin(), graph[v][u].end(), nonterm) == graph[v][u].end()) {
                graph[v][u].push_back(nonterm);
                altered = true;
            }
        }
    }

    if (len == 0)
        return;

    for (int to = 0; to < (int)graph.size(); to++) {
        if (!graph[u][to].empty()) {
            for (string pth: graph[u][to]) {
                string newPath = currPath + pth;
                dfs(to, v, newPath, len - 1);
            }
        }
    }
}


void GLRSolver::solve() {
    assert(!grammar.empty() && !graph.empty() && output != "" && "Invalid params!");

    int N = (int)graph.size();

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (std::string label : graph[i][j])
                if (!grammar[label].empty())
                    graph[i][j].push_back(*grammar[label].begin());


    int mx = -INT32_MIN;
    for (auto rule : grammar)
        mx = MAX(mx, (int) rule.first.length());

    do {
        altered = false;
        for (int i = 0; i < N; i++)
            dfs(i, i, "", mx);
    } while (altered);

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