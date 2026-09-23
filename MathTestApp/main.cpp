#include <iostream>
#include "MathTest.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "=== MathTest ===\n";
    std::cout << "Тренировка устного счёта.\n\n";

    int count;
    std::cout << "Сколько примеров? ";
    std::cin >> count;

    try {
        MathTest test(count, 1, 20);
        test.run();
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}