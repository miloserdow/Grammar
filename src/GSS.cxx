//
// Created by milos on 1/23/18.
//


#include <tuple>
#include <GSS.h>
#include "utils.h"

GSS::GSS(const std::string& nonTerminal, int pos) {
    nTerm = nonTerminal;
    posD = pos;
    poppedPos = std::vector<int>(0);
}

std::vector<Configuration> GSS::pop(int pos) {
    std::vector<Configuration> result = std::vector<Configuration>(0);
    for (auto &edge: edges)
        result.emplace_back(Configuration(pos, std::get<0>(edge), std::get<1>(edge)));
    popped = true;
    for (auto &finalPos : poppedPos)
        if (finalPos == pos)
            return result;
    poppedPos.push_back(pos);
    return result;
}


std::vector<Configuration> GSS::addEdge(int returnPos, int p) {
    std::vector<Configuration> result = std::vector<Configuration>(0);
    for (auto &edge : edges)
        if (std::get<0>(edge) == returnPos && std::get<1>(edge) == p)
            return result;
    edges.emplace_back(std::make_pair(returnPos, p));
    if (popped)
        for (auto pos: poppedPos)
            result.emplace_back(Configuration(pos, returnPos, p));
    return result;

}
