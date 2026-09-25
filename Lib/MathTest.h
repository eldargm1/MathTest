#pragma once
#include "Task.h"

class MathTest {
private:
    Task* tasks;
    int count;
    int* user_answers;
    int correct_count;

    void init(int count);

public:
    MathTest(int count);
    MathTest(int count, int min, int max);
    MathTest(int count, int min, int max, char operation);
    ~MathTest() noexcept;

    int getCount() const noexcept;
    int getCorrectCount() const noexcept;
    int getUserAnswer(int index) const;
    const Task& getTask(int index) const;

    void run();
    void show_statistics() const;
    bool checkAnswer(int index, int userAnswer);
};