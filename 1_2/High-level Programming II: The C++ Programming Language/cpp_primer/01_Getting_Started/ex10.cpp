// In addition to the ++ operator that adds 1 to its operand,
// there is a decrement operator (--) that subtracts 1. Use the decrement
// operator to write a while that prints the numbers from ten down to zero.
#include <iostream>

int main() {
    int count = 10;
    while (count >= 0) {
        std::cout << count << " and counting..," << std::endl;
        --count;
    }

    return 0;
}