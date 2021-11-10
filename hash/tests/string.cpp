//
// Created by mateu on 09.11.2021.
//
#include <vector>
#include "../hashset.h"
#include "../hashed_types.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
namespace TestString {
    using SetType = HashSet<String>;
    vector<String> testData({{"Liam"},
                             {"Noah"},
                             {"Oliver"},
                             {"Elijah"},
                             {"William"},
                             {"James"},
                             {"Benjamin"},
                             {"Lucas"},
                             {"Henry"},
                             {"Alexander"},
                             {"Mason"},
                             {"Michael"},
                             {"Ethan"},
                             {"Daniel"},
                             {"Jacob"},
                             {"Logan"},
                             {"Jackson"},
                             {"Levi"},
                             {"Sebastian"},
                             {"Mateo"}});
#define TestName TestString
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