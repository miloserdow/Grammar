//
// Created by milos on 1/4/18.
//

#ifndef GLLSOLVER_H
#define GLLSOLVER_H

#include <queue>
#include "utils.h"
#include "AbstractSolver.h"
#include <GSS.h>

typedef std::vector<GSS> gss_t;
typedef std::vector<std::pair<int, int> > edge_t;

class GLLSolver : public AbstractSolver {
    automaton_t automaton, RFA;
    start_states_t startStatesR;
    final_states_t finalStatesR, start_nonTerm;
    state_edge_t edgesA, edgesR;
    std::queue<Configuration> q;
    std::vector<Configuration> used;
    gss_t G;
    std::vector<std::string> nTerms;
    std::string output;
    int curIdx, nStatesA, nStatesR;

    void _init();
    gss_t::iterator findNodePos(int);
    int addGSSNode(GSS&, int&);
    void addConf(const Configuration&);

public:
    GLLSolver(const std::string &gramInp, const std::string &graphInp, std::string output) {
        readRfa(gramInp, RFA, nStatesR, startStatesR, finalStatesR);
        readAutomaton(graphInp, automaton, nStatesA);
        this->output = output;
        this->curIdx = 0;
        this->_init();
    }

    void solve() override;
};
#endif //GLLSOLVER_H