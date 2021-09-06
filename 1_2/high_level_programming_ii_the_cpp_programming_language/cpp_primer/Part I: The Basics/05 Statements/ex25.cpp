// Revise your program from the previous exercise to use a try block to catch the exception.
// The catch clause should print a message to the user and ask them to supply a new number and repeat the code inside the try.
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
                        "\nTry again: " << std::endl;
        }

    return 0;
}
