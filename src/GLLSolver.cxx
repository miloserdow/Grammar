//
// Created by milos on 1/4/18.
//

#include <algorithm>
#include <queue>
#include "GLLSolver.h"

using namespace std;

inline bool isTerminal(rfa_t RFA, string s) {
    return RFA.find(s) == RFA.end();
}

void GLLSolver::solve() {
    set<string> ans;

    for (int z = 0; z < graph.size(); z++) {
        queue<Configuration> q;
        vector<Configuration> popped;
        pair_t start = make_pair("S", z);
        GSS gss(start);
        q.push(Configuration(z, make_pair("S", 0), start));
        while (!q.empty()) {
            Configuration cur_conf = q.front();
            q.pop();
            if (find(popped.begin(), popped.end(), cur_conf) != popped.end())
                continue;

            popped.push_back(cur_conf);
            int graphPosition = cur_conf.position;
            auto module = grammar[cur_conf.RFAPosition.first];
            int modulePosition = cur_conf.RFAPosition.second;
            if (modulePosition == module.size() - 1) {
                pair_t node = cur_conf.node;
                ans.insert(node.first + "," + to_string(node.second) + "," + to_string(graphPosition));
                vector<ppair_t> pairOfPairs = gss.getNodes(node);
                for (ppair_t ppair : pairOfPairs) {
                    Configuration conf(graphPosition, ppair.first, ppair.second);
                    q.push(conf);
                }
            }

            for (int i = 0; i < module.size(); i++) {
                for (string edgeRFA : module[modulePosition][i]) {
                    if (isTerminal(grammar, edgeRFA)) {
                        for (int j = 0; j < graph.size(); j++) {
                            for (const string &edgeGraph : graph[graphPosition][j]) {
                                if (edgeRFA == edgeGraph) {
                                    Configuration conf(j, make_pair(cur_conf.RFAPosition.first, i), cur_conf.node);
                                    q.push(conf);
                                }
                            }
                        }
                    } else {
                        Configuration conf(graphPosition,
                            make_pair(edgeRFA, 0),
                            make_pair(edgeRFA, graphPosition));
                        q.push(conf);
                        gss.add(make_pair(cur_conf.RFAPosition.first, i),
                                make_pair(edgeRFA, graphPosition),
                                cur_conf.node);
                    }
                }
            }
        }
    }


    ofstream fout(output);
    for (const string &s : ans) {
        fout << s << endl;
    }
    fout.close();
}