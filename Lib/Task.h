#pragma once
#include <string>

struct Task {
    int num_1;
    int num_2;
    char operation;
    int answer;

    // Конструктор по умолчанию — случайный пример
    Task();

    // Конструктор с диапазоном и опциональной операцией
    // operation = '\0' означает "любая операция"
    Task(int min, int max, char operation = '\0');

private:
    // Вспомогательный метод: генерирует пример по диапазону и операции
    void generate(int min, int max, char op);

    // Вычисляет правильный ответ по num_1, num_2, operation
    int calculate() const;
};
