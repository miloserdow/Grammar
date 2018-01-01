//
// Created by milos on 12/30/17.
//

#include "MatrixSolver.h"
#include "gtest/gtest.h"

class MatrixSolverTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    MatrixSolverTest() {
        // You can do set-up work for each test here.
    }

    virtual ~MatrixSolverTest() {
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

    MatrixSolver solver;
};

TEST_F(MatrixSolverTest, BasicTest) {
    EXPECT_EQ(0,0);
}
