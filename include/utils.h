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

// I will just leave it here...
typedef std::map<std::string, std::vector<std::string> >      grammar_t;
typedef std::vector<std::vector<std::vector<std::string> > >  graph_t;
typedef std::vector<std::vector<bool> > matrix_t;
typedef std::vector<std::tuple<int, int, const std::string> > automaton_t;
typedef std::map<int, std::vector<std::string> > start_states_t;
typedef std::map<std::string, std::vector<int> > final_states_t;
typedef std::vector<std::pair<int, int>> idx_arr_t;
typedef std::vector<std::string> right_part_t;
typedef std::map<std::string, std::vector<right_part_t> > grammar2_t;
typedef std::map<std::string, std::vector<std::vector<std::set<std::string> > > > rfa_t;

namespace {

inline right_part_t split(std::string &s, char d) {
    right_part_t res;
    std::stringstream stringStream(s);
    std::string l;
    while (std::getline(stringStream, l, d))
        if (!l.empty())
            res.push_back(l);
    return res;
}

void readAutomaton(const std::string &fileName, automaton_t &automaton, int &nStates) {
    std::ifstream fin(fileName);
    std::string cur;
    std::regex rule0("[0-9]+");

    do {
        std::getline(fin, cur);
    } while (!std::regex_search(cur, rule0));
    nStates = (int)split(cur, ';').size();

    std::regex rule1("([0-9]+)( -> )([0-9]+)([^0-9]+\")([^\"]*)(\"])+"), bracket("[}]+");
    std::smatch res;
    while (std::getline(fin, cur)) {
        if (cur.empty())
            continue;

        if (!std::regex_search(cur, bracket)) {
            if (std::regex_search(cur, res, rule1)) {
                automaton.emplace_back(std::make_tuple<int, int, const std::string>(std::stoi(res.str(1)), std::stoi(res.str(3)), res.str(5)));
            }
        } else break;
    }
    fin.close();
}

void readRfa(const std::string &fileName, automaton_t &automation, int &nStates, start_states_t &startStates, final_states_t &finalStates) {
    std::ifstream fin(fileName);
    std::string cur;
    std::regex rule0("[0-9]+");

    do {
        std::getline(fin, cur);
    } while (!std::regex_search(cur, rule0));

    nStates = (int)split(cur, ';').size();
    std::regex rule1("([0-9]+)([[])"), rule2("(->)"), rule3("(color=)"), rule4("(shape=)"), rule5("(label=\")([^\"]+)"), rule6("([0-9]+)");
    std::smatch res;
    while (!std::regex_search(cur, res, rule1))
        std::getline(fin, cur);

    std::string label;
    int numOfStateInDef;

    while (!std::regex_search(cur, res, rule2)) {
        if (cur.empty()) {
            std::getline(fin, cur);
            continue;
        }

        if (std::regex_search(cur, res, rule6))
            numOfStateInDef = std::stoi(res.str(1));

        if (std::regex_search(cur, res, rule5)) {
            label = res.str(2);
            if (std::regex_search(cur, res, rule3)) {
                auto states = std::vector<std::string>(1, label);
                auto emplaceResult = startStates.emplace(numOfStateInDef, states);
                if (!std::get<1>(emplaceResult)) {
                    auto it = std::get<0>(emplaceResult);
                    (*it).second.push_back(label);
                }
            }

            if (std::regex_search(cur, res, rule4)) {
                auto states = std::vector<int>(1, numOfStateInDef);
                auto result = finalStates.emplace(label, states);
                if (!std::get<1>(result)) {
                    auto it = std::get<0>(result);
                    (*it).second.push_back(numOfStateInDef);
                }
            }
        }
        std::getline(fin, cur);
    }

    std::regex aRule("([0-9]+)( -> )([0-9]+)([^0-9]+\")([^\"]*)(\"])+");
    std::regex bracket("[}]+");
    do {
        if (cur.empty())
            continue;
        if (!std::regex_search(cur, bracket)) {
            if (std::regex_search(cur, res, aRule))
                automation.emplace_back(std::make_tuple<int, int, const std::string>(std::stoi(res.str(1)), std::stoi(res.str(3)), res.str(5)));
        } else break;
    } while (std::getline(fin, cur));
    fin.close();
}

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
