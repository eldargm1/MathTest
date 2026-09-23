#include "pch.h"
#include "Task.h"
#include <stdexcept>

// Проверяем, что конструктор по умолчанию создаёт валидную задачу
TEST(TaskTest, DefaultConstructor) {
    Task t;
    EXPECT_GE(t.num_1, 1);
    EXPECT_LE(t.num_1, 10);
    EXPECT_GE(t.num_2, 1);
    EXPECT_LE(t.num_2, 10);
    EXPECT_TRUE(t.operation == '+' || t.operation == '-' ||
        t.operation == '*' || t.operation == '/');
}

// Проверяем, что answer соответствует операции
TEST(TaskTest, AnswerIsCorrect) {
    Task t;
    int expected = 0;
    switch (t.operation) {
    case '+': expected = t.num_1 + t.num_2; break;
    case '-': expected = t.num_1 - t.num_2; break;
    case '*': expected = t.num_1 * t.num_2; break;
    case '/': expected = t.num_1 / t.num_2; break;
    }
    EXPECT_EQ(t.answer, expected);
}

// Проверяем конструктор с диапазоном
TEST(TaskTest, ConstructorWithRange) {
    Task t(5, 20);
    EXPECT_GE(t.num_1, 5);
    EXPECT_LE(t.num_1, 20 * 20);  // для деления num_1 может быть больше max
    EXPECT_GE(t.num_2, 5);
    EXPECT_LE(t.num_2, 20);
}

// Проверяем конструктор с заданной операцией '+'
TEST(TaskTest, ConstructorWithOperationPlus) {
    Task t(1, 100, '+');
    EXPECT_EQ(t.operation, '+');
    EXPECT_EQ(t.answer, t.num_1 + t.num_2);
}

// Проверяем конструктор с заданной операцией '*'
TEST(TaskTest, ConstructorWithOperationMul) {
    Task t(1, 10, '*');
    EXPECT_EQ(t.operation, '*');
    EXPECT_EQ(t.answer, t.num_1 * t.num_2);
}

// Проверяем, что деление всегда нацело
TEST(TaskTest, DivisionIsExact) {
    Task t(1, 100, '/');
    EXPECT_EQ(t.operation, '/');
    EXPECT_EQ(t.num_1 % t.num_2, 0);  // делится без остатка
}

// Проверяем исключение при min > max
TEST(TaskTest, ThrowsOnInvalidRange) {
    EXPECT_THROW(Task(10, 5), std::invalid_argument);
}

// Проверяем исключение при недопустимой операции
TEST(TaskTest, ThrowsOnInvalidOperation) {
    EXPECT_THROW(Task(1, 10, '%'), std::invalid_argument);
}