#include "MathTest.h"
#include <stdexcept>
#include <iostream>    // ← добавь
#include <iomanip>     // ← добавь (для std::setw)
#include <string>      // ← добавь (для std::to_string)

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

// --- Проверка ответа (без ввода-вывода!) ---
bool MathTest::checkAnswer(int index, int userAnswer) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    user_answers[index] = userAnswer;
    bool correct = (userAnswer == tasks[index].answer);
    if (correct) {
        correct_count++;
    }
    return correct;
}

// --- Запуск теста (общение с пользователем) ---
void MathTest::run() {
    std::cout << "\n=== Начало теста ===\n";
    std::cout << "Вам будет задано " << count << " вопросов.\n\n";

    for (int i = 0; i < count; ++i) {
        const Task& t = tasks[i];
        std::cout << "Вопрос " << (i + 1) << "/" << count << ": ";
        std::cout << t.num_1 << " " << t.operation << " " << t.num_2 << " = ";

        int userAnswer;
        std::cin >> userAnswer;

        bool correct = checkAnswer(i, userAnswer);
        if (correct) {
            std::cout << "  Верно!\n";
        }
        else {
            std::cout << "  Неверно. Правильный ответ: " << t.answer << "\n";
        }
    }

    std::cout << "\n=== Тест завершён ===\n";
    show_statistics();
}

// --- Вывод таблицы результатов ---
void MathTest::show_statistics() const {
    // Верхняя граница таблицы
    std::cout << "\n|          No |";
    for (int i = 1; i <= count; ++i) {
        std::cout << " " << std::setw(8) << i << " |";
    }
    std::cout << "\n+";
    for (int i = 0; i < count + 1; ++i) {
        std::cout << "----------+";
    }
    std::cout << "\n";

    // Вопросы
    std::cout << "|    Question |";
    for (int i = 0; i < count; ++i) {
        std::string q = std::to_string(tasks[i].num_1) + " " +
            tasks[i].operation + " " +
            std::to_string(tasks[i].num_2);
        std::cout << " " << std::setw(8) << q << " |";
    }
    std::cout << "\n";

    // Правильные ответы
    std::cout << "| True Answer |";
    for (int i = 0; i < count; ++i) {
        std::cout << " " << std::setw(8) << tasks[i].answer << " |";
    }
    std::cout << "\n";

    // Ответы пользователя
    std::cout << "| Your Answer |";
    for (int i = 0; i < count; ++i) {
        std::cout << " " << std::setw(8) << user_answers[i] << " |";
    }
    std::cout << "\n";

    // Результаты (+/-)
    std::cout << "|      Result |";
    for (int i = 0; i < count; ++i) {
        char mark = (user_answers[i] == tasks[i].answer) ? '+' : '-';
        std::cout << " " << std::setw(8) << mark << " |";
    }
    std::cout << "\n\n";

    // Итог
    std::cout << "Total Result: " << correct_count << " / " << count << "\n";
}