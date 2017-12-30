//
// Created by milos on 12/30/17.
//

#ifndef GRAMMAR_UTILS_H
#define GRAMMAR_UTILS_H

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>


typedef std::map<std::string, std::vector<std::string> >      grammar_t;
typedef std::vector<std::vector<std::vector<std::string> > >  graph_t;

namespace {

void readGrammarFromFile(std::string ifname, grammar_t &grammar) {
    std::ifstream gfin(ifname);
    std::string l, sep, r;
    while (gfin >> l >> sep >> r) {
        grammar[r].push_back(l);
    }
    gfin.close();
}

void readGraphFromFile(std::string ifname, graph_t &graph) {
    std::ifstream fin(ifname);
    std::string l1, l2, l3;
    getline(fin, l1);
    getline(fin, l2);
    getline(fin, l3);
    int N = std::count(l3.begin(), l3.end(), ';');

    std::vector<std::vector<std::vector<std::string> > > G(N,
                                                           std::vector<std::vector<std::string> >(N,
                                                                                                  std::vector<std::string>()));
    std::string cur;
    for (;;) {
        int a, b;
        std::string label;

        char ch = fin.get();
        if (ch && !isdigit(ch))
            break;
        fin.putback(ch);
        getline(fin, cur);
        std::stringstream is(cur);

        std::string sep, ending;
        is >> a >> sep >> ending;

        std::string num(ending);
        int pos = 0;
        while (isdigit(num[pos++]));
        num = num.substr(0, pos - 1);
        ending = ending.substr(pos + 7, ending.length() - pos);

        std::string num2(ending);
        pos = 0;
        while (isalnum(num2[pos++]));
        num2 = num2.substr(0, pos - 1);

        std::stringstream is2(num + ' ' + num2);
        is2 >> b >> label;
        G[a][b].push_back(label);
    }
    fin.close();
    graph = G;
}

} // end anonymous namespace

#endif //GRAMMAR_UTILS_H
