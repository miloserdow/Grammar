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
#include <iostream>
#include <cassert>
#include <set>
#include <regex>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef std::map<std::string, std::vector<std::string> >      grammar_t;
typedef std::vector<std::vector<std::vector<std::string> > >  graph_t;

typedef std::map<std::string, std::vector<std::vector<std::set<std::string> > > > rfa_t;

namespace {

rfa_t readRFA(const std::string &ifname) {
    std::ifstream fin(ifname);
    std::map<std::string, std::vector<std::string> > mp;
    std::string l, sep, r;
    while (fin >> l >> sep >> r) {
        mp[l].push_back(r);
    }
    fin.close();

    rfa_t RFA;
    for (auto elem : mp) {
        std::string key = elem.first;
        auto list = elem.second;
        size_t size = 0;
        for (std::string s : list) {
            size += s.length();
        }
        size -= list.size();
        size += 2;

        assert(size > 0 && "Size should be >0!");
        std::vector<std::vector<std::set<std::string> > > module(size,
                std::vector<std::set<std::string> >(size));

        int i = 0;
        for (std::string right : list) {
            if (right.length() == 1) {
                module[0][size - 1].insert(right);
                continue;
            }
            for (int j = 0; j < right.length(); j++) {
                if (j == right.length() - 1) {
                    module[i][size - 1].insert(std::string(1, right[j]));
                } else {
                    if (j == 0)
                        module[0][i + 1].insert(std::string(1, right[j]));
                    else
                        module[i][i + 1].insert(std::string(1, right[j]));
                    i++;
                }
            }
        }
        RFA[key] = module;
    }
    return RFA;
}

void readGrammarFromFile(const std::string &ifname, grammar_t &grammar) {
    std::ifstream gfin(ifname);
    std::string l, sep, r;
    while (gfin >> l >> sep >> r) {
        grammar[r].push_back(l);
    }
    gfin.close();
}

void readGraphFromFile(const std::string &ifname, graph_t &graph) {
    std::ifstream fin(ifname);
    std::string l1, l2, l3;
    getline(fin, l1);
    getline(fin, l2);
    getline(fin, l3);
    long N = std::count(l3.begin(), l3.end(), ';');

    std::vector<std::vector<std::vector<std::string> > > G(N,
                                                           std::vector<std::vector<std::string> >(N,
                                                                                                  std::vector<std::string>()));
    std::string cur;
    for (;;) {
        int a, b;
        std::string label;

        char ch = static_cast<char>(fin.get());
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

int countResFile(const std::string &ifname, char S) {
    std::ifstream fin(ifname);
    std::string line;
    int res = 0;
    while (std::getline(fin, line)) {
        res += std::count(line.begin(), line.end(), S);
    }
    return res;
}

} // end anonymous namespace

#endif //GRAMMAR_UTILS_H
