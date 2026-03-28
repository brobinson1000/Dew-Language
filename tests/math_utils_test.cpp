// tests/math_utils_test.cpp
#include <gtest/gtest.h>
extern "C" {
    #include "math_utils.h"
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(MathUtilsTest, Floor) {
    EXPECT_EQ(math_floor("3.7"), 3);
    EXPECT_EQ(math_floor("-2.3"), -3);
    EXPECT_EQ(math_floor("5"), 5);
    EXPECT_EQ(math_floor("-5"), -5);
}

TEST(MathUtilsTest, Ceil) {
    EXPECT_EQ(math_ceil("3.2"), 4);
    EXPECT_EQ(math_ceil("-2.7"), -2);
    EXPECT_EQ(math_ceil("5"), 5);
    EXPECT_EQ(math_ceil("-5"), -5);
}

TEST(MathUtilsTest, Abs) {
    EXPECT_EQ(math_abs("5"), 5);
    EXPECT_EQ(math_abs("-5"), 5);
    EXPECT_EQ(math_abs("0"), 0);
}

TEST(MathUtilsTest, Pi) {
    EXPECT_DOUBLE_EQ(math_pi(), 3.14159265358979323846);
}

TEST(MathUtilsTest, Sqrt) {
    EXPECT_EQ(math_sqrt("64"), 8);
    EXPECT_EQ(math_sqrt("49"), 7);
}

TEST(MathUtilsTest, Pow) {
    EXPECT_EQ(math_pow("2 3"), 8);
}

TEST(MathUtilsTest, Hypot) {
    EXPECT_EQ(math_hypot("2 3"),  3.6055512754639891);
}
