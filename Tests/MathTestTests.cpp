#include "pch.h"
#include "MathTest.h"
#include <stdexcept>

TEST(MathTestTest, ConstructorBySize) {
    MathTest m(5);
    EXPECT_EQ(m.getCount(), 5);
    EXPECT_EQ(m.getCorrectCount(), 0);
}

TEST(MathTestTest, ConstructorBySizeAndRange) {
    MathTest m(3, 1, 10);
    EXPECT_EQ(m.getCount(), 3);
    for (int i = 0; i < 3; ++i) {
        EXPECT_GE(m.getTask(i).num_1, 1);
        EXPECT_LE(m.getTask(i).num_1, 100);
        EXPECT_GE(m.getTask(i).num_2, 1);
        EXPECT_LE(m.getTask(i).num_2, 10);
    }
}

TEST(MathTestTest, ConstructorWithOperation) {
    MathTest m(3, 1, 10, '+');
    EXPECT_EQ(m.getCount(), 3);
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(m.getTask(i).operation, '+');
    }
}

TEST(MathTestTest, ThrowsOnZeroCount) {
    EXPECT_THROW(MathTest(0), std::invalid_argument);
    EXPECT_THROW(MathTest(-1), std::invalid_argument);
}

TEST(MathTestTest, CheckAnswerCorrect) {
    MathTest m(1, 1, 10, '+');
    int correct = m.getTask(0).answer;
    bool result = m.checkAnswer(0, correct);
    EXPECT_TRUE(result);
    EXPECT_EQ(m.getCorrectCount(), 1);
    EXPECT_EQ(m.getUserAnswer(0), correct);
}

TEST(MathTestTest, CheckAnswerWrong) {
    MathTest m(1, 1, 10, '+');
    int wrong = m.getTask(0).answer + 999;
    bool result = m.checkAnswer(0, wrong);
    EXPECT_FALSE(result);
    EXPECT_EQ(m.getCorrectCount(), 0);
    EXPECT_EQ(m.getUserAnswer(0), wrong);
}

TEST(MathTestTest, MultipleAnswers) {
    MathTest m(3, 1, 10, '+');
    m.checkAnswer(0, m.getTask(0).answer);
    m.checkAnswer(1, 999);
    m.checkAnswer(2, m.getTask(2).answer);
    EXPECT_EQ(m.getCorrectCount(), 2);
}

TEST(MathTestTest, CheckAnswerTwice) {
    MathTest m(1, 1, 10, '+');
    m.checkAnswer(0, m.getTask(0).answer);
    EXPECT_EQ(m.getCorrectCount(), 1);
    m.checkAnswer(0, 999);
    EXPECT_EQ(m.getCorrectCount(), 0);
}

TEST(MathTestTest, ThrowsOnOutOfRange) {
    MathTest m(2, 1, 10);
    EXPECT_THROW(m.getTask(5), std::out_of_range);
    EXPECT_THROW(m.getUserAnswer(-1), std::out_of_range);
    EXPECT_THROW(m.checkAnswer(99, 0), std::out_of_range);
}

TEST(MathTestTest, GettersWork) {
    MathTest m(4);
    EXPECT_EQ(m.getCount(), 4);
    EXPECT_EQ(m.getCorrectCount(), 0);
    EXPECT_EQ(m.getUserAnswer(0), 0);
}