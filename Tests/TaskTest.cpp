#include "pch.h"
#include "Task.h"
#include <stdexcept>

TEST(TaskTest, DefaultConstructor) {
    Task t;
    EXPECT_GE(t.num_1, 1);
    EXPECT_LE(t.num_1, 100);
    EXPECT_GE(t.num_2, 1);
    EXPECT_LE(t.num_2, 10);
    EXPECT_TRUE(t.operation == '+' || t.operation == '-' ||
        t.operation == '*' || t.operation == '/');
}

TEST(TaskTest, AnswerIsCorrect) {
    Task t;
    int expected = 0;
    switch (t.operation) {
    case '+': expected = t.num_1 + t.num_2; break;
    case '-': expected = t.num_1 - t.num_2; break;
    case '*': expected = t.num_1 * t.num_2; break;
    case '/': expected = t.num_1 / t.num_2; break;
    default:  FAIL() << "Unknown operation"; return;
    }
    EXPECT_EQ(t.answer, expected);
}

TEST(TaskTest, ConstructorWithRange) {
    Task t(5, 20);
    EXPECT_GE(t.num_1, 5);
    EXPECT_LE(t.num_1, 400);
    EXPECT_GE(t.num_2, 5);
    EXPECT_LE(t.num_2, 20);
}

TEST(TaskTest, ConstructorWithOperationPlus) {
    Task t(1, 100, '+');
    EXPECT_EQ(t.operation, '+');
    EXPECT_EQ(t.answer, t.num_1 + t.num_2);
}

TEST(TaskTest, ConstructorWithOperationMul) {
    Task t(1, 10, '*');
    EXPECT_EQ(t.operation, '*');
    EXPECT_EQ(t.answer, t.num_1 * t.num_2);
}

TEST(TaskTest, DivisionIsExact) {
    Task t(1, 100, '/');
    EXPECT_EQ(t.operation, '/');
    EXPECT_EQ(t.num_1 % t.num_2, 0);
}

TEST(TaskTest, ThrowsOnInvalidRange) {
    EXPECT_THROW(Task(10, 5), std::invalid_argument);
}

TEST(TaskTest, ThrowsOnInvalidOperation) {
    EXPECT_THROW(Task(1, 10, '%'), std::invalid_argument);
}