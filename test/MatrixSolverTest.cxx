//
// Created by milos on 12/30/17.
//

#include "MatrixSolver.h"
#include "gtest/gtest.h"

#define RESDAT "res.dat"


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
        L = "../test/grammars/Grammar1";
        L2 = "../test/grammars/Grammar2";
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    std::string L, L2, G;
    AbstractSolver *solver;
};

TEST_F(MatrixSolverTest, SkosTest) {
    G = "../test/graphs/skos.dot";

    solver = new MatrixSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 810);

    solver = new MatrixSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 1);
}


TEST_F(MatrixSolverTest, AtomTest) {
    G = "../test/graphs/atom-primitive.dot";

    solver = new MatrixSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 15454);

    solver = new MatrixSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 122);
}

TEST_F(MatrixSolverTest, BioTest) {
    G = "../test/graphs/biomedical-mesure-primitive.dot";

    solver = new MatrixSolver(L, G, RESDAT);
    solver->solve();
    delete solver;

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 15156);

    solver = new MatrixSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 2871);
}

TEST_F(MatrixSolverTest, FoafTest) {
    G = "../test/graphs/foaf.dot";

    solver = new MatrixSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 4118);

}


TEST_F(MatrixSolverTest, FundingTest) {
    G = "../test/graphs/funding.dot";

    solver = new MatrixSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 17634);

    solver = new MatrixSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 1158);
}

TEST_F(MatrixSolverTest, GenerationsTest) {
    G = "../test/graphs/generations.dot";

    solver = new MatrixSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 2164);

    solver = new MatrixSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 0);
}

TEST_F(MatrixSolverTest, PplPetsTest) {
    G = "../test/graphs/people_pets.dot";

    solver = new MatrixSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 9472);

    solver = new MatrixSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 37);
}

TEST_F(MatrixSolverTest, TravelTest) {
    G = "../test/graphs/travel.dot";

    solver = new MatrixSolver(L, G, RESDAT);
    solver->solve();

    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 2499);
}

TEST_F(MatrixSolverTest, UnivTest) {
    G = "../test/graphs/univ-bench.dot";

    solver = new MatrixSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 2540);

    solver = new MatrixSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 81);
}

TEST_F(MatrixSolverTest, WineTest) {
    G = "../test/graphs/wine.dot";

    solver = new MatrixSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 66572);

    solver = new MatrixSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 133);
}

TEST_F(MatrixSolverTest, PizzaTest) {
    G = "../test/graphs/pizza.dot";

    solver = new MatrixSolver(L, G, RESDAT);
    solver->solve();
    int res = countResFile(RESDAT, 'S');
    EXPECT_EQ(res, 56195);

    solver = new MatrixSolver(L2, G, RESDAT);
    solver->solve();
    int res1 = countResFile(RESDAT, 'S');
    EXPECT_EQ(res1, 1262);
}