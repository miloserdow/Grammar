cmake_minimum_required(VERSION 3.9)
project(Grammar)

set(CMAKE_CXX_STANDARD 11)

add_executable(Grammar
        driver.cxx MatrixSolver.cxx MatrixSolver.h AbstractSolver.h utils.h)
