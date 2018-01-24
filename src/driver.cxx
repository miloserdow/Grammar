#include <iostream>
#include <GLRSolver.h>
#include <GLLSolver.h>
#include "utils.h"
#include "MatrixSolver.h"

int main(int argc, char* argv[]) {
    if (argc != 4 && argc != 3) {
        std::cerr << "Usage: ./grammar <grammar file> <graph file> <output file>\n";
        std::cerr << "or: ./grammar <grammar file> <graph file>\n";
        exit(1);
    }

    std::string s1(argv[1]), s2(argv[2]), s3;
    if (argc == 3) {
        s3 = "/dev/stdout";
    } else {
        s3 = std::string(argv[3]);
    }
    std::cout << "select algo to run:\n1. Matrix\n2. GLR\n3. GLL\nYour choice: ";
    std::cout.flush();

    int type;
    std::cin >> type;
    AbstractSolver *solver;
    switch (type) {
        case 1:
            if (s1.find(".dot") != std::string::npos)
                std::cerr << "WARNING: Matrix solver does not support Graphvis grammar input!" << std::endl;
            solver = new MatrixSolver(s1, s2, s3);
            break;
        case 2:
            solver = new GLRSolver(s1, s2, s3);
            break;
        case 3:
            solver = new GLLSolver(s1, s2, s3);
            break;
        default:
            std::cerr << "Wrong choice :(" << std::endl;
            exit(1);
    }

    solver->solve();
    if (argc == 4)
        std::cout << "Solver done solving, please check result in " << s3 << std::endl;
    return 0;
}