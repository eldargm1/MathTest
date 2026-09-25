#include "MathTest.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <string>

MathTest::MathTest(int count) {
    init(count);
    for (int i = 0; i < count; ++i) {
        tasks[i] = Task();
    }
}

MathTest::MathTest(int count, int min, int max) {
    init(count);
    for (int i = 0; i < count; ++i) {
        tasks[i] = Task(min, max);
    }
}

MathTest::MathTest(int count, int min, int max, char operation) {
    init(count);
    for (int i = 0; i < count; ++i) {
        tasks[i] = Task(min, max, operation);
    }
}

MathTest::~MathTest() noexcept {
    delete[] tasks;
    delete[] user_answers;
}

void MathTest::init(int count) {
    if (count <= 0) {
        throw std::invalid_argument("Count must be > 0");
    }
    this->count = count;
    this->correct_count = 0;
    this->tasks = new Task[count];
    this->user_answers = new int[count];
    for (int i = 0; i < count; ++i) {
        user_answers[i] = 0;
    }
}

int MathTest::getCount() const noexcept { return count; }
int MathTest::getCorrectCount() const noexcept { return correct_count; }

int MathTest::getUserAnswer(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index out of range");
    }
    return user_answers[index];
}

const Task& MathTest::getTask(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index out of range");
    }
    return tasks[index];
}

bool MathTest::checkAnswer(int index, int userAnswer) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index out of range");
    }

    bool wasCorrect = (user_answers[index] == tasks[index].answer);
    if (wasCorrect) {
        correct_count--;
    }

    user_answers[index] = userAnswer;
    bool isCorrect = (userAnswer == tasks[index].answer);
    if (isCorrect) {
        correct_count++;
    }
    return isCorrect;
}

void MathTest::run() {
    std::cout << "\n=== Test started ===\n";
    std::cout << "You will be asked " << count << " questions.\n\n";

    for (int i = 0; i < count; ++i) {
        const Task& t = tasks[i];
        std::cout << "Question " << (i + 1) << "/" << count << ": ";
        std::cout << t.num_1 << " " << t.operation << " " << t.num_2 << " = ";

        int userAnswer;
        std::cin >> userAnswer;

        if (checkAnswer(i, userAnswer)) {
            std::cout << "  Correct!\n";
        }
        else {
            std::cout << "  Wrong. Correct answer: " << t.answer << "\n";
        }
    }

    std::cout << "\n=== Test finished ===\n";
    show_statistics();
}

void MathTest::show_statistics() const {
    std::cout << "\n|          No |";
    for (int i = 1; i <= count; ++i) {
        std::cout << " " << std::setw(8) << i << " |";
    }
    std::cout << "\n+";
    for (int i = 0; i < count + 1; ++i) {
        std::cout << "----------+";
    }
    std::cout << "\n";

    std::cout << "|    Question |";
    for (int i = 0; i < count; ++i) {
        std::string q = std::to_string(tasks[i].num_1) + " " +
            tasks[i].operation + " " +
            std::to_string(tasks[i].num_2);
        std::cout << " " << std::setw(8) << q << " |";
    }
    std::cout << "\n";

    std::cout << "| True Answer |";
    for (int i = 0; i < count; ++i) {
        std::cout << " " << std::setw(8) << tasks[i].answer << " |";
    }
    std::cout << "\n";

    std::cout << "| Your Answer |";
    for (int i = 0; i < count; ++i) {
        std::cout << " " << std::setw(8) << user_answers[i] << " |";
    }
    std::cout << "\n";

    std::cout << "|      Result |";
    for (int i = 0; i < count; ++i) {
        char mark = (user_answers[i] == tasks[i].answer) ? '+' : '-';
        std::cout << " " << std::setw(8) << mark << " |";
    }
    std::cout << "\n\n";

    std::cout << "Total Result: " << correct_count << " / " << count << "\n";
}