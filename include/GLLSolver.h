//
// Created by milos on 1/4/18.
//

#ifndef GRAMMAR_GLLSOLVER_H
#define GRAMMAR_GLLSOLVER_H

#include <queue>
#include "utils.h"
#include "AbstractSolver.h"

typedef std::pair<std::string, int> pair_t;
typedef std::pair<pair_t, pair_t> ppair_t;

class GSS {
    std::vector<std::vector<std::vector<int> > > gss;
    std::map<int, pair_t> gssVertices;
    std::map<int, pair_t> gssEdges;
    int countEdge;
    int countVertices;
public:
    GSS(pair_t pair) {
        gss = std::vector<std::vector<std::vector<int> > >(1024, std::vector<std::vector<int> >(1024));
        gssEdges[0] = pair;
        countEdge = 1;
        countVertices = 0;
    }

    void add(pair_t vertex, pair_t fromEdge, pair_t toEdge) {
        std::vector<ppair_t> nodes = getNodes(fromEdge);
        if (nodes.empty()) {
            gssEdges[countEdge] = fromEdge;
            int from = countEdge;
            countEdge++;
            int to = getIndexEdge(toEdge);
            gssVertices[countVertices] = vertex;
            gss[from][to].push_back(countVertices);
            countVertices++;
            return;
        }

        for (ppair_t pop : nodes) {
            pair_t v = pop.first, e = pop.second;
            if (v == vertex && e == toEdge)
                return;
        }
        int indexEdgeFrom = getIndexEdge(fromEdge);
        int indexEdgeTo = getIndexEdge(toEdge);
        gssVertices[countVertices] = vertex;

        gss[indexEdgeFrom][indexEdgeTo].push_back(countVertices);
        countVertices++;
    }

    int getIndexEdge(pair_t edge) {
        for (auto elem : gssEdges) {
            int i = elem.first;
            pair_t pair = elem.second;
            if (pair == edge)
                return i;
        }
        return -1;
    }

    std::vector<ppair_t> getNodes(pair_t edge) {
        int indexEdge = getIndexEdge(edge);

        std::vector<ppair_t> ans;
        if (indexEdge == -1)
            return ans; // empty

        for (int i = 0; i < gss.size(); i++) {
            if (!gss[indexEdge][i].empty()) {
                for (int j : gss[indexEdge][i]) {
                    pair_t a = gssVertices[j];
                    pair_t b = gssEdges[i];
                    ans.push_back(std::make_pair(a, b));
                }
            }
        }
        return ans;
    }
};

class Configuration {
public:
    int position;
    pair_t RFAPosition;
    pair_t node;
    Configuration(int pos, pair_t R, pair_t n) {
        this->position = pos;
        this->RFAPosition = R;
        this->node = n;
    }

    bool operator==(const Configuration& other) const {
        return position == other.position && RFAPosition == other.RFAPosition
                && node == other.node;
    }
};

class GLLSolver : public AbstractSolver {
    rfa_t grammar;
public:
    GLLSolver(const rfa_t& grammar, const graph_t& graph, std::string output = "res.dat") {
        this->grammar = grammar;
        this->graph = graph;
        this->output = output;
    }
    virtual void solve();
};

#endif //GRAMMAR_GLLSOLVER_H