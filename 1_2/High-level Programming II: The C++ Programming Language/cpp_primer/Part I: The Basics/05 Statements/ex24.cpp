// Revise your program to throw an exception if the second number is zero.
// Test your program with a zero input to see what happens on your system if you don’t catch an exception.
#include <iostream>

int main() {
    int dividend, divisor;
    double result = 0.0;

    while (std::cin >> dividend >> divisor)
        try {
            if (divisor == 0)
                throw std::out_of_range("0 cannot be a divisor.");
            result = static_cast<double>(dividend) / divisor;
            std::cout << dividend << " / " << divisor << " is " << result << std::endl;
        } catch(const std::exception& e) {
            std::cerr << e.what() <<
                        "\nTry again? Enter y of n: " << std::endl;
            char c;
            std::cin >> c;
            if (!std::cin || c == 'n')
                break;
        }

    return 0;
}

// If nothing is read, the program does nothing and terminates