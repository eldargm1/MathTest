#pragma once
#include "Task.h"

class MathTest {
private:
    Task* tasks;
    int count;
    int* user_answers;
    int correct_count;

public:
    MathTest(int count);
    MathTest(int count, int min, int max);
    MathTest(int count, int min, int max, char operation);
    ~MathTest();

    int getCount() const;
    int getCorrectCount() const;
    int getUserAnswer(int index) const;
    const Task& getTask(int index) const;

    // НОВОЕ:
    void run();
    void show_statistics() const;
    bool checkAnswer(int index, int userAnswer);
};