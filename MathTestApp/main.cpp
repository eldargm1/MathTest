#include <iostream>
#include "MathTest.h"

int main() {
    std::cout << "=== MathTest ===\n";
    std::cout << "Mental math training.\n\n";

    int count;
    std::cout << "How many questions? ";
    if (!(std::cin >> count)) {
        std::cerr << "Error: enter a number\n";
        return 1;
    }

    try {
        MathTest test(count, 1, 20);
        test.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}