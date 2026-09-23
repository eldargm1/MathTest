#pragma once
#include "Task.h"

class MathTest {
private:
    Task* tasks;          // массив вопросов
    int count;            // количество вопросов
    int* user_answers;    // ответы пользователя
    int correct_count;    // сколько правильных

public:
    // Конструкторы
    MathTest(int count);
    MathTest(int count, int min, int max);
    MathTest(int count, int min, int max, char operation);

    // Деструктор
    ~MathTest();

    // Геттеры
    int getCount() const;
    int getCorrectCount() const;
    int getUserAnswer(int index) const;
    const Task& getTask(int index) const;
};

// Ctrl+S — сохранить
