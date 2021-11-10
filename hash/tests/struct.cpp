//
// Created by mateu on 09.11.2021.
//
#include <iostream>
#include "../hashset.h"
#include "../hashed_types.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
namespace TestStruct {
    using SetType = HashSet<Struct>;
    vector<Struct> testData({{234525345, 1.5809106109565494e+38,  342289496416},
                             {2567626, -7.280442044414199e+237, 4646464955462121},
                             {10,        -8.215134356185921e+45,  10},
                             {10,        8.737606871357179e+307,  10},
                             {-42312, 1.7483045327392457e+7, 8647},
                             {-34660, 3.483058787362059e+307, 76806874},
                             {-123123, 6.916195061133739e+307, 45452345},
                             {-675712312, 1.576513466558128e+66, 4534}});
#define TestName TestStruct
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
        set.insert(testData[1]);
        set.insert(testData[3]);
        set.insert(testData[5]);
        set.remove(testData[3]);
        ASSERT_FALSE(set.contains(testData[3]));
        ASSERT_TRUE(set.contains(testData[1]));
        ASSERT_TRUE(set.contains(testData[5]));
    }
}