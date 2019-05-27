// Write a program that uses a while to sum the numbers from 50 to 100.
#include <iostream>

int main() {
    int sum = 0, count = 50;
    while (count <= 100) {
        sum += count;
        ++count;
    }
    std::cout << "The sum of the numbers from 50 to 100 is "
                << sum << std::endl;

    return 0;
}