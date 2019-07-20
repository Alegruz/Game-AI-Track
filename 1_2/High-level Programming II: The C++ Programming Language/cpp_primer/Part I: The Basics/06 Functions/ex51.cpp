// Write all four versions of f.
// Each function should print a distinguishing message.
// Check your answers for the previous exercise.
// If your answers were incorrect,
// study this section until you understand why your answers were wrong.
#include <iostream>

void f();
void f(int);
void f(int, int);
void f(double, double = 3.14);

int main() {
    f();
    f(3);
    f(0, 3);
    f(5.6);
    f(3.2, 3.4);

    return 0;
}

void f() {
    std::cout << "NO PARAMETER" << std::endl;
}

void f(int i) {
    std::cout << "SINGLE INT: " << i << std::endl;
}

void f(int i1, int i2) {
    std::cout << "DOUBLE INT: " << i1 << ", " << i2 << std::endl;
}

void f(double d1, double d2) {
    std::cout << "SINGLE OR DOUBLE DOUBLE: " << d1 << ", " << d2 << std::endl;
}