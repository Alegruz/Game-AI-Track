// Revise the program you wrote for the exercises in § 1.4.1 (p. 13)
// that printed a range of numbers so that it handles input in which the first
// number is smaller than the second. (ex11.cpp)

#include <iostream>

int main() {
    std::cout << "Enter two integers that represents a range: ";
    int v1 = 0, v2 = 0;
    while (!(std::cin >> v1 >> v2) || v1 > v2)
        std::cout << "Input Invalid. Please enter TWO INTEGERS that represents a RANGE: ";

    while (v1 <= v2) {
        std::cout << v1 << " and counting..." << std::endl;
        ++v1;
    }

    return 0;
}