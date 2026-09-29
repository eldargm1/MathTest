#pragma once

struct Task {
    int num_1;
    int num_2;
    char operation;
    int answer;

    Task();

    Task(int min, int max, char operation = '\0');

private:
    void generate(int min, int max, char op);

    int calculate() const;
};