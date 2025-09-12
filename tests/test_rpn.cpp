#include <gtest/gtest.h>
#include "rpn.h"
#include <stdexcept>

TEST(RPNTest, BasicAddition) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("2 3 +"), 5.0);
}

TEST(RPNTest, Subtraction) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("5 3 -"), 2.0);
}

TEST(RPNTest, Multiplication) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("4 3 *"), 12.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("2.5 4 *"), 10.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("-2 3 *"), -6.0);
}

TEST(RPNTest, Division) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("10 2 /"), 5.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("7 2 /"), 3.5);
    EXPECT_DOUBLE_EQ(evaluate_rpn("-6 2 /"), -3.0);
}

TEST(RPNTest, DivisionByZero) {
    EXPECT_THROW(evaluate_rpn("1 0 /"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("5 0.0 /"), std::invalid_argument);
}

TEST(RPNTest, ComplexExpression) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("2 3 * 4 +"), 10.0);      // (2*3)+4 = 10
    EXPECT_DOUBLE_EQ(evaluate_rpn("10 2 / 3 *"), 15.0);     // (10/2)*3 = 15
    EXPECT_DOUBLE_EQ(evaluate_rpn("5 1 2 + 4 * + 3 -"), 14.0); // 5 + ((1+2)*4) - 3 = 14
}

TEST(RPNTest, InvalidExpression) {
    EXPECT_THROW(evaluate_rpn("2 +"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("+"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("2 3 4 +"), std::invalid_argument); // слишком много операндов
    EXPECT_THROW(evaluate_rpn("2 3 * *"), std::invalid_argument); // недостаточно операндов
}

TEST(RPNTest, InvalidToken) {
    EXPECT_THROW(evaluate_rpn("2 3 ^"), std::invalid_argument); // неверный оператор
    EXPECT_THROW(evaluate_rpn("2 3 x"), std::invalid_argument); // неверный токен
}

TEST(RPNTest, SingleNumber) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("42"), 42.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("3.14"), 3.14);
}

TEST(RPNTest, MultipleSpaces) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("  2   3   +  "), 5.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("4   2   *   "), 8.0);
}
