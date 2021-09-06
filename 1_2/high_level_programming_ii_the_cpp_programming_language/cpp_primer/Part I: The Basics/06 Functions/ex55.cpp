// Write four functions that add, subtract, multiply, and divide two int values.
// Store pointers to these values in your vector from the previous exercise.
#include <vector>

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

int main() {
    std::vector<decltype(add) *> calculations = {add, subtract, multiply, divide};

    return 0;
}