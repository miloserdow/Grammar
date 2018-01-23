//
// Created by milos on 1/4/18.
//

#include <iostream>
#include <fstream>
#include <GLLSolver.h>

inline bool isNTerm(const std::string &s) {
    return ((s.length() != 1 && s != "eps")
            || (!islower(s[0]) && !isdigit(s[0])));
}

void GLLSolver::solve() {
    for (int i = 0; i < nStatesA; ++ i) {
        for (auto &nTerm : nTerms) {
            GSS node(nTerm, i);
            node.pos = curIdx++;
            G.emplace_back(node);
            auto it = start_nonTerm.find(nTerm);
            if (it != start_nonTerm.end()) {
                for (auto &iter : it->second) {
                    q.push(Configuration(i, iter, node.pos));
                    used.emplace_back(Configuration(i, iter, node.pos));
                }
            }
        }
    }

    while (!q.empty()) {
        Configuration config = q.front(); q.pop();
        auto ei = edgesA.find(config.posA);
        if (ei != edgesA.end()) {
            auto eir = edgesR.find(config.posR);
            if (eir != edgesR.end()) {
                for (auto &it1 : ei->second) {
                    for (auto &it2 : eir->second) {
                        if (it1.second == it2.second)
                            addConf(Configuration(it1.first, it2.first, config.pos));
                    }
                }
            }
        }

        auto edge1 = edgesR.find(config.posR);
        if (edge1 != edgesR.end()) {
            for (auto &pairRFA : (*edge1).second) {
                if (isNTerm(pairRFA.second)) {
                    auto node = GSS(pairRFA.second, config.posA);
                    int pos = addGSSNode(node, curIdx);
                    auto it = findNodePos(pos);
                    auto it2 = it->addEdge(pairRFA.first, config.pos);
                    for (auto &conf : it2)
                        addConf(conf);

                    auto iter = start_nonTerm.find(pairRFA.second);
                    if (iter != start_nonTerm.end())
                        for (auto start : iter->second)
                            addConf(Configuration(config.posA, start, pos));
                }
            }
        }

        auto snode = findNodePos(config.pos);
        std::string nT = snode->nTerm;
        auto it = finalStatesR.find(nT);
        assert(it != finalStatesR.end() && "error, impossible situation");

        for (int stateRFA : it->second) {
            if (stateRFA == config.posR) {
                auto res = snode->pop(config.posA);
                for (const Configuration &conf : res)
                    addConf(conf);
            }
        }
    }

    std::ofstream fout(output);
    for (GSS& gssNode : G)
        if (gssNode.popped)
            for (auto &finalPos : gssNode.poppedPos)
                fout << gssNode.posD << "," << gssNode.nTerm << "," << finalPos << "\n";
    fout.close();
}

void GLLSolver::addConf(const Configuration& conf) {
    if (std::find(used.begin(), used.end(), conf) == used.end()) {
        q.push(conf);
        used.push_back(conf);
    }
}

int GLLSolver::addGSSNode(GSS &node, int &id) {
    for (auto &iter : G)
        if ((node.posD == iter.posD)
            && (node.nTerm == iter.nTerm))
            return iter.pos;
    node.pos = id, id++;
    G.push_back(node);
    return node.pos;
}


void GLLSolver::_init() {
    int s;
    std::pair<int, std::string> mem;
    for (auto &r : automaton) {
        mem = std::make_pair(std::get<1>(r), std::get<2>(r));
        out_edge_t dest = std::vector<std::pair<int, std::string> >(1, mem);
        s = std::get<0>(r);
        auto pos = edgesA.emplace(s, dest);
        if (!pos.second)
            pos.first->second.push_back(mem);
    }
    for (auto &r : RFA) {
        std::string c = std::get<2>(r);
        mem = std::make_pair(std::get<1>(r), c);
        out_edge_t dest = std::vector<std::pair<int, std::string> >(1, mem);
        s = std::get<0>(r);
        auto pos = edgesR.emplace(s, dest);
        if (!pos.second)
            pos.first->second.push_back(mem);
    }
    for (auto &it : finalStatesR)
        nTerms.push_back(it.first);
    for (auto &it : startStatesR) {
        for (auto &nTerm : it.second) {
            auto it2 = start_nonTerm.emplace(nTerm, std::vector<int>(1, it.first));
            if (!it2.second)
                it2.first->second.push_back(it.first);
        }
    }
}

gss_t::iterator GLLSolver::findNodePos(int p) {
    for (auto it = G.begin(); it != G.end(); it++)
        if (it->pos == p)
            return it;
    return G.end();
}