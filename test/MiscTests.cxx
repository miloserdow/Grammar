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
#define HARDTESTANSWER 1

class MiscTests : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    MiscTests() : L {"../test/grammars/AnBn", "../test/grammars/Ambigious", "../test/grammars/Regex", "../test/grammars/Hard"},
                  G {"../test/graphs/cycle.dot", "../test/graphs/line.dot", "../test/graphs/regex.dot", "../test/graphs/hard.dot"} {
        // You can do set-up work for each test here.
    }

    virtual ~MiscTests() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp() {

    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    const std::string L[4];
    const std::string G[4];
};

TEST_F(MiscTests, CycleTest) {
    MatrixSolver matrixSolver(L[0], G[0]);
    matrixSolver.solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, CYCLETESTANSWER);
}

TEST_F(MiscTests, Cycle2Test) {
    // a bit different case but almost same filename
    GLRSolver glr(L[0]+".dot", G[0], RESDAT);
    glr.solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 6);

    GLLSolver gll(L[0]+".dot", G[0], RESDAT);
    gll.solve();
    int res2 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res2, 6);
}

// Tests for CNF only
TEST_F(MiscTests, LineTest) {
    MatrixSolver matrixSolver(L[1], G[1]);
    matrixSolver.solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, LINETESTANSWER);
}

TEST_F(MiscTests, RegexTest) {
    MatrixSolver matrixSolver(L[2], G[2]);
    matrixSolver.solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, REGTESTANSWER);
}

TEST_F(MiscTests, HardTest) {
    MatrixSolver matrixSolver(L[3], G[3]);
    matrixSolver.solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, HARDTESTANSWER);
}

// Tests for graphvis here
TEST_F(MiscTests, iTest1) {
    int res;
    std::string iL = "../test/grammars/itest1.dot", iG = "../test/graphs/itest1.dot";

    GLRSolver glr(iL, iG, RESDAT);
    glr.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 16);

    GLLSolver gll(iL, iG, RESDAT);
    gll.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 16);
}

TEST_F(MiscTests, iTest2) {
    int res;
    std::string iL = "../test/grammars/itest2.dot", iG = "../test/graphs/itest2.dot";

    GLRSolver glr(iL, iG, RESDAT);
    glr.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 20);

    GLLSolver gll(iL, iG, RESDAT);
    gll.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 20);
}

TEST_F(MiscTests, iTest3) {
    int res;
    std::string iL = "../test/grammars/itest3.dot", iG = "../test/graphs/itest3.dot";

    GLRSolver glr(iL, iG, RESDAT);
    glr.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 1);

    GLLSolver gll(iL, iG, RESDAT);
    gll.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 1);
}

TEST_F(MiscTests, iTest4) {
    int res;
    std::string iL = "../test/grammars/itest4.dot", iG = "../test/graphs/itest4.dot";

    GLRSolver glr(iL, iG, RESDAT);
    glr.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 9);

    GLLSolver gll(iL, iG, RESDAT);
    gll.solve();
    res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 9);
}