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

    GLLSolver solver(argv[1], argv[2], argv[3]);
    solver.solve();
    return 0;
}