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


    std::cout << "Select algo to run:\n1. Matrix\n2. GLR\n3. GLL\nYour choice: ";
    std::cout.flush();

    int type;
    std::cin >> type;
    AbstractSolver *solver;
    std::string s(argv[1]);
    switch (type) {
        case 1:
            if (s.find(".dot") != std::string::npos)
                std::cerr << "WARNING: Matrix solver does not support Graphvis grammar input!" << std::endl;
            solver = new MatrixSolver(argv[1], argv[2], argv[3]);
            break;
        case 2:
            solver = new GLRSolver(argv[1], argv[2], argv[3]);
            break;
        case 3:
            solver = new GLLSolver(argv[1], argv[2], argv[3]);
            break;
        default:
            std::cerr << "Wrong choice :(" << std::endl;
            exit(1);
    }

    solver->solve();
    std::cout << "Solver done solving, please check result in " << argv[3] << std::endl;
    return 0;
}