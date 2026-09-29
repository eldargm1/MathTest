#pragma once
#include "Task.h"
#include <vector>

class MathTest {
private:
    std::vector<Task> tasks;
    std::vector<int> userAnswers;
    std::vector<bool> answered;
    int count = 0;
    int correctCount = 0;

    void init(int count);

public:
    MathTest(int count);
    MathTest(int count, int min, int max);
    MathTest(int count, int min, int max, char operation);

    int getCount() const noexcept;
    int getCorrectCount() const noexcept;
    int getUserAnswer(int index) const;
    const Task& getTask(int index) const;

    void run();
    void showStatistics() const;
    bool checkAnswer(int index, int userAnswer);
};