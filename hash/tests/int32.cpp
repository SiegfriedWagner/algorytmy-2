//
// Created by mateu on 09.11.2021.
//
#include <iostream>
#include "../hashset.h"
#include "../hashed_types.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace std;

TEST(TESTHello, First) {
    HashSet<Int32> set;
    set.insert({10});
    set.insert({20});
    set.insert({33});
    set.insert({87});
}
