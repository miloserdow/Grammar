#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
#include <set>


using namespace std;

int main() {
    ifstream gfin("Grammar1");
    string l, sep, r;
    map<string, vector<string> > L;
    while (gfin >> l >> sep >> r) {
        L[r].push_back(l);
    }
    gfin.close();
    
    ifstream fin("skos.dot");
    string l1, l2, l3;
    getline(fin, l1);
    getline(fin, l2);
    getline(fin, l3);
    int N = count(l3.begin(), l3.end(), ';');
    
    vector<vector<vector<string> > > G(N, vector<vector<string> >(N, vector<string>()));
    string cur;
    for (;;) {
        int a, b;
        string label;
        
        char ch = fin.get();
        if (ch && !isdigit(ch))
            break;
        fin.putback(ch);
        getline(fin, cur);
        stringstream is(cur);
        
        string sep, ending;
        is >> a >> sep >> ending;
        
        string num(ending); int pos = 0;
        while (isdigit(num[pos++]));
        num = num.substr(0, pos-1);
        ending = ending.substr(pos+7, ending.length() - pos);
        
        string num2(ending); pos = 0;
        while (isalnum(num2[pos++]));
        num2 = num2.substr(0, pos-1);
        
        stringstream is2(num+' '+num2);
        is2 >> b >> label;
        cout << a << " " << b << " " << label << '\n';
        
        if (!L[label].empty())
            G[a][b].push_back(*L[label].begin());
        else
            G[a][b].push_back(label);
    }
    fin.close();

    bool changed = true;
    while (changed) {
        changed = false;
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    vector<string> start = G[i][k];
                    vector<string> finish = G[k][j];
                    for (string s : start) {
                        for (string f : finish) {
                            string n = s + f;
                            if (L.find(n) != L.end()) {
                                vector<string> concat = L[n];
                                for (string elem : concat) {
                                    if (find(G[i][j].begin(), G[i][j].end(), elem) == G[i][j].end()) {
                                        G[i][j].push_back(elem);
                                        changed = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    ofstream fout("res.dat");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!G[i][j].empty()) {
                for (string str : G[i][j]) {
                    fout << i << "," << str << "," << j << "\n";
                }
            }
        }
    }
    return 0;
}
