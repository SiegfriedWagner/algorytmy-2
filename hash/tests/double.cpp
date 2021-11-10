//
// Created by mateu on 09.11.2021.
//
#include "../hashset.h"
#include "../hashed_types.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
namespace TestDouble {
    using SetType = HashSet<Double>;
    constexpr array<Double, 20> testData = {1.5809106109565494e+38,
                                            -7.280442044414199e+237,
                                            -8.215134356185921e+45,
                                            8.737606871357179e+307,
                                            1.7483045327392457e+7,
                                            3.483058787362059e+307,
                                            6.916195061133739e+307,
                                            1.576513466558128e+66,
                                            -1.9888625129115988e+307,
                                            -1.4297108555501598e+238,
                                            -1.781512272908282e+308,
                                            -1.2961676273172808e+308,
                                            7.101436213160955e+78,
                                            -1.0499797016839581e+102,
                                            1.7844176486775225e+155,
                                            -5.807042489942582e+2,
                                            9.30612333223046e+34,
                                            6.691021201303547e+306,
                                            -1.2481455506370372e+82,
                                            -1.6551392673948025e+308};
#define TestName TestDouble
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