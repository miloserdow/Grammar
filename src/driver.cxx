#include <iostream>
#include <GLRSolver.h>
#include <GLLSolver.h>
#include "utils.h"
#include "MatrixSolver.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./grammar <grammar file> <graph file> <output file>\n";
        exit(1);
    }

   // rfa_t L = readRFA(argv[1]);

    grammar_t L;
    readGrammarFromFile(argv[1], L);
    graph_t G;
    readGraphFromFile(argv[2], G);
    MatrixSolver solver(L, G);
    solver.solve();
   // GLLSolver solver(L, G);
   // solver.solve();

    return 0;
}