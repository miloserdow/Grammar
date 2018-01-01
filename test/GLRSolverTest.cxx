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
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    graph_t G;
    grammar_t L;
    AbstractSolver *solver;
};

TEST_F(GLRSolverTest, SkosTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/skos.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 810);
}


TEST_F(GLRSolverTest, AtomTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/atom-primitive.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 15454);
}

TEST_F(GLRSolverTest, BioTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/biomedical-mesure-primitive.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 15156);
}

TEST_F(GLRSolverTest, FoafTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/foaf.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 4118);
}


TEST_F(GLRSolverTest, FundingTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/funding.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 17634);
}

TEST_F(GLRSolverTest, GenerationsTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/generations.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 2164);
}

TEST_F(GLRSolverTest, PplPetsTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/people_pets.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 9472);
}

TEST_F(GLRSolverTest, TravelTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/travel.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 2499);
}

TEST_F(GLRSolverTest, UnivTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/univ-bench.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');

    EXPECT_EQ(res, 2540);
}

TEST_F(GLRSolverTest, WineTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/wine.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 66572);
}

TEST_F(GLRSolverTest, PizzaTest) {
    readGrammarFromFile("../test/grammars/Grammar1", L);
    readGraphFromFile("../test/graphs/pizza.dot", G);

    solver = new GLRSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 56195);
}