//
// Created by milos on 1/23/18.
//


#ifndef GSS_H
#define GSS_H

#include <vector>
#include <iostream>

typedef std::vector<std::pair<int, int> > edge_t;

class Configuration;

class GSS {
public:
    GSS(const std::string&, int);
    std::vector<Configuration> pop(int);
    std::vector<Configuration> addEdge(int, int);

    std::string nTerm;
    int posD, pos;
    bool popped = false;
    edge_t edges;
    std::vector<int> poppedPos;
};

class Configuration {
public:
    int pos, posA, posR;

    Configuration(int curPosDFA = 0, int curGrm = 0, int sp = 0) {
        posA = curPosDFA;
        posR = curGrm;
        pos = sp;
    }

    bool operator==(const Configuration& rhs) const {
        return posR == rhs.posR && posA == rhs.posA && pos == rhs.pos;
    }

    bool operator!=(const Configuration& rhs) const {
        return !(*this == rhs);
    }
};

#endif //GSS_H
