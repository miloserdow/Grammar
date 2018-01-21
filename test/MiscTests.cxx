//
// Created by milos on 12/30/17.
//

#include <GLRSolver.h>
#include <MatrixSolver.h>
#include "GLLSolver.h"
#include "gtest/gtest.h"

#define RESDAT "res.dat"

#define LINETESTANSWER 15
#define REGTESTANSWER 1
#define CYCLETESTANSWER 3

class MiscTests : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    MiscTests() {
        // You can do set-up work for each test here.
    }

    virtual ~MiscTests() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp() {
        RFA[0] = readRFA("../test/grammars/Ambigious");
        readGrammarFromFile("../test/grammars/Ambigious", L[0]);

        RFA[1] = readRFA("../test/grammars/AnBn");
        readGrammarFromFile("../test/grammars/AnBn", L[1]);

        RFA[3] = readRFA("../test/grammars/Regex");
        readGrammarFromFile("../test/grammars/Regex", L[3]);

        readGraphFromFile("../test/graphs/cycle.dot", G[0]);
        readGraphFromFile("../test/graphs/line.dot", G[1]);
        readGraphFromFile("../test/graphs/regex.dot", G[3]);
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    graph_t G[4];
    grammar_t L[4];
    rfa_t RFA[4];
    AbstractSolver *solver;
};

TEST_F(MiscTests, CycleTest) {
    GLRSolver glr(L[1], G[0]); // cycle + AnBn
    glr.solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, CYCLETESTANSWER);

    MatrixSolver matrixSolver(L[1], G[0]);
    matrixSolver.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, CYCLETESTANSWER);

    GLLSolver gll(RFA[1], G[0]);
    gll.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, CYCLETESTANSWER);
}

TEST_F(MiscTests, LineTest) {
    GLRSolver glr(L[0], G[1]); // line + Ambigious
    glr.solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, LINETESTANSWER);

    MatrixSolver matrixSolver(L[0], G[1]);
    matrixSolver.solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, LINETESTANSWER);

    GLLSolver gll(RFA[0], G[1]);
    gll.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, LINETESTANSWER);
}

TEST_F(MiscTests, RegexTest) {
    GLRSolver glr(L[3], G[3]); // regex + Regex
    glr.solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, REGTESTANSWER);

    MatrixSolver matrixSolver(L[3], G[3]);
    matrixSolver.solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, REGTESTANSWER);

    GLLSolver gll(RFA[3], G[3]);
    gll.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, REGTESTANSWER);
}