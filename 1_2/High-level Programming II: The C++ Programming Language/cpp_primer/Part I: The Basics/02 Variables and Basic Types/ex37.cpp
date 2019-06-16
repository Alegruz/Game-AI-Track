// Assignment is an example of an expression that yields a reference type.
// The type is a reference to the type of the left-hand operand.
// That is, if i is an int, then the type of the expression i = x is int&.
// Using that knowledge, determine the type and value of each variable in this code:
#include <iostream>

int main() {
    int a = 3, b = 4;   // a: int, 3
                        // b: int, 4
    decltype(a) c = a;  // c: int, 3
    decltype(a = b) d = a;  // d: int &, 3

    std::cout << "a: " << a << '\n'
            << "b: " << b << '\n'
            << "c: " << c << '\n'
            << "d: " << d << std::endl;

    return 0;
}