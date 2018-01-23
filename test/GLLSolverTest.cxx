//
// Created by milos on 12/30/17.
//

#include "GLLSolver.h"
#include "gtest/gtest.h"

#define RESDAT "res.dat"

class GLLSolverTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    GLLSolverTest() {
        // You can do set-up work for each test here.
    }

    virtual ~GLLSolverTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp() {
        L  = readRFA("../test/grammars/Grammar1");
        L2 = readRFA("../test/grammars/Grammar2");
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    graph_t G;
    rfa_t L, L2;
    AbstractSolver *solver;
};

TEST_F(GLLSolverTest, SkosTest) {
    readGraphFromFile("../test/graphs/skos.dot", G);

    solver = new GLLSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 810);

    solver = new GLLSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 1);
}


TEST_F(GLLSolverTest, AtomTest) {
    readGraphFromFile("../test/graphs/atom-primitive.dot", G);

    solver = new GLLSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 15454);

    solver = new GLLSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 122);
}

TEST_F(GLLSolverTest, BioTest) {
    readGraphFromFile("../test/graphs/biomedical-mesure-primitive.dot", G);

    solver = new GLLSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 15156);

    GLLSolver solver1(L2, G, RESDAT);
    solver1.solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 2871);
}

TEST_F(GLLSolverTest, FoafTest) {
    readGraphFromFile("../test/graphs/foaf.dot", G);

    solver = new GLLSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 4118);

}


TEST_F(GLLSolverTest, FundingTest) {
    readGraphFromFile("../test/graphs/funding.dot", G);

    solver = new GLLSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 17634);

    solver = new GLLSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 1158);
}

TEST_F(GLLSolverTest, GenerationsTest) {
    readGraphFromFile("../test/graphs/generations.dot", G);

    solver = new GLLSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 2164);

    solver = new GLLSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 0);
}

TEST_F(GLLSolverTest, PplPetsTest) {
    readGraphFromFile("../test/graphs/people_pets.dot", G);

    solver = new GLLSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 9472);

    solver = new GLLSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 37);
}

TEST_F(GLLSolverTest, TravelTest) {
    readGraphFromFile("../test/graphs/travel.dot", G);

    solver = new GLLSolver(L, G, RESDAT);
    solver->solve();

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 2499);
}

TEST_F(GLLSolverTest, UnivTest) {
    readGraphFromFile("../test/graphs/univ-bench.dot", G);

    solver = new GLLSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 2540);

    solver = new GLLSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 81);
}

TEST_F(GLLSolverTest, WineTest) {
    readGraphFromFile("../test/graphs/wine.dot", G);

    solver = new GLLSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 66572);

    solver = new GLLSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 133);
}

TEST_F(GLLSolverTest, PizzaTest) {
    readGraphFromFile("../test/graphs/pizza.dot", G);

    solver = new GLLSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 56195);

    solver = new GLLSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 1262);
}