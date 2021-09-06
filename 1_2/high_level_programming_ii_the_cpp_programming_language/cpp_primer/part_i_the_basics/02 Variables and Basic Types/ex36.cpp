// In the following code, determine the type of each variable and the value each variable has when the code finishes:
#include <iostream>

int main() {
    int a = 3, b = 4;   // a and b is int, a is 3, b is 4
    decltype(a) c = a;  // c is int, c is 3
    decltype((b)) d = a;    // d is a reference to int, d is a, which is 3
    ++c;    // c is 4
    ++d;    //d is 4, a is 4
    // a: int, 4
    // b: int, 4
    // c: int, 4
    // d: int &, 4

    std::cout << "a: " << a << '\n'
              << "b: " << b << '\n'
              << "c: " << c << '\n'
              << "d: " << d << std::endl;
    return 0;
}
