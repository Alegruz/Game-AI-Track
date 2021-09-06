// Call each element in the vector and print their result.
#include <vector>
#include <iostream>

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

int main() {
    std::vector<decltype(add) *> calculations = {add, subtract, multiply, divide};

    std::cout << calculations[0](3, 2) << std::endl;
    std::cout << calculations[1](3, 2) << std::endl;
    std::cout << calculations[2](3, 2) << std::endl;
    std::cout << calculations[3](3, 2) << std::endl;

    return 0;
}