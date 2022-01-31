//
// Created by mateu on 27.01.2022.
//
#include "../cnf_solver.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace std;
#define TestName TEST2CNF
#define TRUE 1
#define FALSE (-1)
TEST(TestName, TestTerms1) {
    vector<int> right = {1, -2, -1, 3, -3, -4, -3};
    vector<int> left =  {2,  3, -2, 4, 5, -5, 4};
    CNF2Solver solver(getNumberOfTermsHelper(left, right));
    for (int i = 0; i < right.size(); ++i) {
        solver.addOrPair(left[i], right[i]);
    }
    auto solution = solver.solve();
    ASSERT_EQ(6, solution.size());
    ASSERT_EQ(TRUE, solution[1]); // x1
    ASSERT_EQ(FALSE, solution[2]); // x2
    ASSERT_EQ(FALSE, solution[3]); // x3
    ASSERT_EQ(TRUE, solution[4]); // x4
    ASSERT_EQ(FALSE, solution[5]); // x5
}

TEST(TestName, TestTerms2) {
    vector<int> right = {1, -1};
    vector<int> left = {1, -1};
    CNF2Solver solver(getNumberOfTermsHelper(left, right));
    for (int i = 0; i < right.size(); ++i) {
        solver.addOrPair(left[i], right[i]);
    }
    auto solution = solver.solve();
    ASSERT_EQ(0, solution.size());
}