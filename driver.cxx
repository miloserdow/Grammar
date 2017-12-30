#include <iostream>
#include "utils.h"
#include "MatrixSolver.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./grammar <grammar file> <graph file> <output file>\n";
        exit(1);
    }

    grammar_t L;
    readGrammarFromFile(argv[1], L);

    graph_t G;
    readGraphFromFile(argv[2], G);

    MatrixSolver solver(L, G);
    solver.solve();

    return 0;
}