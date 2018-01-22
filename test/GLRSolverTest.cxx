//
// Created by milos on 12/30/17.
//

#include "GLRSolver.h"
#include "gtest/gtest.h"

#define RESDAT "res.dat"

class GLRSolverTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    GLRSolverTest() {
        // You can do set-up work for each test here.
    }

    virtual ~GLRSolverTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp() {
        readGrammarFromFile("../test/grammars/Grammar1", L);
        readGrammarFromFile("../test/grammars/Grammar2", L2);
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    graph_t G;
    grammar_t L, L2;
    AbstractSolver *solver;
};

TEST_F(GLRSolverTest, SkosTest) {
    readGraphFromFile("../test/graphs/skos.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 810);

    solver = new GLRSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 1);
}


TEST_F(GLRSolverTest, AtomTest) {
    readGraphFromFile("../test/graphs/atom-primitive.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 15454);

    solver = new GLRSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 122);
}

TEST_F(GLRSolverTest, BioTest) {
    readGraphFromFile("../test/graphs/biomedical-mesure-primitive.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 15156);

    solver = new GLRSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 5828);
}

TEST_F(GLRSolverTest, FoafTest) {
    readGraphFromFile("../test/graphs/foaf.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 4118);

}


TEST_F(GLRSolverTest, FundingTest) {
    readGraphFromFile("../test/graphs/funding.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 17634);

    solver = new GLRSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 1158);
}

TEST_F(GLRSolverTest, GenerationsTest) {
    readGraphFromFile("../test/graphs/generations.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 2164);

    solver = new GLRSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 0);
}

TEST_F(GLRSolverTest, PplPetsTest) {
    readGraphFromFile("../test/graphs/people_pets.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 9472);

    solver = new GLRSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 37);
}

TEST_F(GLRSolverTest, TravelTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/travel.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 2499);
}

TEST_F(GLRSolverTest, UnivTest) {
    readGraphFromFile("../test/graphs/univ-bench.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 2540);

    solver = new GLRSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 81);
}

TEST_F(GLRSolverTest, WineTest) {
    readGraphFromFile("../test/graphs/wine.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 66572);

    solver = new GLRSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 133);
}

TEST_F(GLRSolverTest, PizzaTest) {
    readGraphFromFile("../test/graphs/pizza.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 56195);

    solver = new GLRSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 1262);
}