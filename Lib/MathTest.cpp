#include "MathTest.h"
#include <stdexcept>

// --- Конструктор 1: по размеру (диапазон по умолчанию 1..10) ---
MathTest::MathTest(int count) {
    if (count <= 0) {
        throw std::invalid_argument("Количество вопросов должно быть > 0");
    }
    this->count = count;
    this->correct_count = 0;
    this->tasks = new Task[count];
    this->user_answers = new int[count];
    for (int i = 0; i < count; ++i) {
        user_answers[i] = 0;
    }
}

// --- Конструктор 2: по размеру + диапазону ---
MathTest::MathTest(int count, int min, int max) {
    if (count <= 0) {
        throw std::invalid_argument("Количество вопросов должно быть > 0");
    }
    this->count = count;
    this->correct_count = 0;
    this->tasks = new Task[count];
    this->user_answers = new int[count];
    for (int i = 0; i < count; ++i) {
        tasks[i] = Task(min, max);
        user_answers[i] = 0;
    }
}

// --- Конструктор 3: по размеру + диапазону + операции ---
MathTest::MathTest(int count, int min, int max, char operation) {
    if (count <= 0) {
        throw std::invalid_argument("Количество вопросов должно быть > 0");
    }
    this->count = count;
    this->correct_count = 0;
    this->tasks = new Task[count];
    this->user_answers = new int[count];
    for (int i = 0; i < count; ++i) {
        tasks[i] = Task(min, max, operation);
        user_answers[i] = 0;
    }
}

// --- Деструктор ---
MathTest::~MathTest() {
    delete[] tasks;
    delete[] user_answers;
}

// --- Геттеры ---
int MathTest::getCount() const { return count; }
int MathTest::getCorrectCount() const { return correct_count; }
int MathTest::getUserAnswer(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return user_answers[index];
}
const Task& MathTest::getTask(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return tasks[index];
}