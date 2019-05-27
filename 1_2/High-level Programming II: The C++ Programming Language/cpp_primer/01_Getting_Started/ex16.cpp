// Write your own version of a program that prints the sum of
// a set of integers read from cin.
#include <iostream>

int main() {
    int i1, i2, sum;
    std::cout << "Enter two integers to add: ";
    std::cin >> i1 >> i2;

    sum = i1 + i2;
    std::cout << "The sum of " << i1 << " and " << i2
                << " is " << sum << std::endl;

    return 0;
}