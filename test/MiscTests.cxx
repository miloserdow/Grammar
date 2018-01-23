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
        _L[0] = "../test/grammars/Ambigious";
        _L[1] = "../test/grammars/AnBn";
        _L[3] = "../test/grammars/Regex";
        _G[0] = "../test/graphs/cycle.dot";
        _G[1] = "../test/graphs/line.dot";
        _G[3] = "../test/graphs/regex.dot";

        RFA[0] = readRFA(_L[0]);
        readGrammarFromFile(_L[0], L[0]);

        RFA[1] = readRFA(_L[1]);
        readGrammarFromFile(_L[1], L[1]);

        RFA[3] = readRFA(_L[3]);
        readGrammarFromFile(_L[3], L[3]);

        readGraphFromFile(_G[0], G[0]);
        readGraphFromFile(_G[1], G[1]);
        readGraphFromFile(_G[3], G[3]);
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    graph_t G[4];
    grammar_t L[4];
    rfa_t RFA[4];

    std::string _L[4], _G[4];
};

TEST_F(MiscTests, CycleTest) {
//    GLRSolver glr(_L[1]+".dot", _G[0], RESDAT); // cycle + AnBn
 //   glr.solve();
  //  int res = countResFile(RESDAT, 'S');
   // EXPECT_EQ(res, CYCLETESTANSWER);

    MatrixSolver matrixSolver(L[1], G[0]);
    matrixSolver.solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, CYCLETESTANSWER);

    GLLSolver gll(RFA[1], G[0]);
    gll.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, CYCLETESTANSWER);
}

TEST_F(MiscTests, LineTest) {
    //GLRSolver glr(_L[0]+".dot", _G[1], RESDAT); // line + Ambigious
   // glr.solve();
   // int res1 = countResFile(RESDAT, 'S');
    //EXPECT_EQ(res1, LINETESTANSWER);

    MatrixSolver matrixSolver(L[0], G[1]);
    matrixSolver.solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, LINETESTANSWER);

    GLLSolver gll(RFA[0], G[1]);
    gll.solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, LINETESTANSWER);
}

TEST_F(MiscTests, RegexTest) {
    //GLRSolver glr(_L[3]+".dot", _G[3], RESDAT); // regex + Regex
    //glr.solve();
    //int res1 = countResFile(RESDAT, 'S');
    //EXPECT_EQ(res1, REGTESTANSWER);

    MatrixSolver matrixSolver(L[3], G[3]);
    matrixSolver.solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, REGTESTANSWER);

    GLLSolver gll(RFA[3], G[3]);
    gll.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, REGTESTANSWER);
}