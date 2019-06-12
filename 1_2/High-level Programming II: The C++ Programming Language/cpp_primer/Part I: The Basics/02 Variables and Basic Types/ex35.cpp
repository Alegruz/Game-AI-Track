// Determine the types deduced in each of the following definitions.
// Once you’ve figured out the types, write a program to see whether you were correct.
#include <iostream>

int main() {
    const int i = 42;
    auto j = i;                 // j: int
    const auto &k = i;          // k: const int &
    auto *p = &i;               // p: const int *
    const auto j2 = i, &k2 = i; // j2: const int, k2: const int &

    std::cout << "i: " << i << sizeof (i) << '\n'
              << "j: " << j << sizeof (j) << '\n'
              << "k: " << k << sizeof (k) << '\n'
              << "*p: " << *p << sizeof (p) << '\n'
              << "j2: " << j2 << sizeof (j2) << '\n'
              << "k2: " << k2 << sizeof (k2) << std::endl;

    return 0;
}
