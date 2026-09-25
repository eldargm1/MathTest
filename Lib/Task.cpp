#include "Task.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>

static bool seeded = false;

static void ensureSeeded() {
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
}

Task::Task() {
    generate(1, 10, '\0');
}

Task::Task(int min, int max, char operation) {
    if (min > max) {
        throw std::invalid_argument("min cannot be greater than max");
    }
    generate(min, max, operation);
}

void Task::generate(int min, int max, char op) {
    ensureSeeded();

    if (op == '\0') {
        const char ops[] = { '+', '-', '*', '/' };
        op = ops[std::rand() % 4];
    }

    if (op != '+' && op != '-' && op != '*' && op != '/') {
        throw std::invalid_argument("Invalid operation");
    }

    operation = op;

    if (op == '/') {
        num_2 = min + std::rand() % (max - min + 1);
        if (num_2 == 0) {
            num_2 = 1;
        }
        int result = min + std::rand() % (max - min + 1);
        num_1 = num_2 * result;
    }
    else {
        num_1 = min + std::rand() % (max - min + 1);
        num_2 = min + std::rand() % (max - min + 1);
    }

    answer = calculate();
}

int Task::calculate() const {
    switch (operation) {
    case '+': return num_1 + num_2;
    case '-': return num_1 - num_2;
    case '*': return num_1 * num_2;
    case '/': return num_1 / num_2;
    default:  throw std::runtime_error("Unknown operation");
    }
}