#include "Task.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>

// Инициализация генератора случайных чисел (один раз)
static bool seeded = false;
static void ensureSeeded() {
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
}

// --- Конструктор по умолчанию ---
Task::Task() {
    generate(1, 10, '\0');  // диапазон 1..10, любая операция
}

// --- Конструктор с диапазоном и операцией ---
Task::Task(int min, int max, char operation) {
    if (min > max) {
        throw std::invalid_argument("min не может быть больше max");
    }
    generate(min, max, operation);
}

// --- Генерация примера ---
void Task::generate(int min, int max, char op) {
    ensureSeeded();

    // Если операция не задана — выбираем случайную из + - * /
    if (op == '\0') {
        const char ops[] = { '+', '-', '*', '/' };
        op = ops[std::rand() % 4];
    }

    // Проверяем, что операция допустима
    if (op != '+' && op != '-' && op != '*' && op != '/') {
        throw std::invalid_argument("Недопустимая операция");
    }

    operation = op;

    // Для деления — генерируем так, чтобы делилось нацело
    if (op == '/') {
        num_2 = min + std::rand() % (max - min + 1);
        if (num_2 == 0) num_2 = 1;  // защита от деления на 0
        int result = min + std::rand() % (max - min + 1);
        num_1 = num_2 * result;
    }
    else {
        num_1 = min + std::rand() % (max - min + 1);
        num_2 = min + std::rand() % (max - min + 1);
    }

    answer = calculate();
}

// --- Вычисление ответа ---
int Task::calculate() const {
    switch (operation) {
    case '+': return num_1 + num_2;
    case '-': return num_1 - num_2;
    case '*': return num_1 * num_2;
    case '/': return num_1 / num_2;
    default:  throw std::runtime_error("Неизвестная операция");
    }
}