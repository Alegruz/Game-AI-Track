// Write a program that reads two integers from the standard input
// and prints the result of dividing the first number by the second.
#include <iostream>

int main() {
    int dividend, divisor;
    double result = 0.0;

    while (std::cin >> dividend >> divisor)
        try {
            if (divisor == 0)
                throw std::out_of_range("0 cannot be a divisor.");
            result = dividend / divisor;
        } catch(const std::exception& e) {
            std::cerr << e.what() <<
                        "\nTry again? Enter y of n: " << std::endl;
            char c;
            std::cin >> c;
            if (!std::cin || c == 'n')
                break;
        }

    std::cout << dividend << " / " << divisor << " is " << result << std::endl;

    return 0;
}
