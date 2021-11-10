//
// Created by mateu on 09.11.2021.
//
#include "../hashset.h"
#include "../hashed_types.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
namespace TestInt64 {
    using SetType = HashSet<Int64>;
    constexpr array<Int64, 20> testData = {10, 20, 33, 87, 82, 24, 85, 35, 20, 4, 10090, 393, 235, 8, 99, 100, 1, 2, 67,
                                           69};
#define TestName TestInt64
    TEST(TestName, CreatingCollection) {
        SetType set;
        for (auto e : testData)
            set.insert(e);
        for (auto e : testData)
            ASSERT_TRUE(set.contains(e));
    }

    TEST(TestName, Duplicates) {
        SetType set;
        set.insert(testData[3]);
        set.insert(testData[3]);
        ASSERT_EQ(set.count(), 1);
    }

    TEST(TestName, AddAndRemove) {
        SetType set;
        set.insert(testData[4]);
        set.insert(testData[8]);
        set.insert(testData[12]);
        set.remove(testData[4]);
        ASSERT_FALSE(set.contains(testData[4]));
        ASSERT_TRUE(set.contains(testData[8]));
        ASSERT_TRUE(set.contains(testData[12]));
    }
}