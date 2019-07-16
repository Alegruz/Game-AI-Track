// Rewrite the program from exercise 6.10 in § 6.2.1 (p. 210)
// to use references instead of pointers to swap the value of two ints.
// Which version do you think would be easier to use and why?
#include <iostream>

void swap(int &a, int &b);

int main() {
    int a = 3, b = 4;

    std::cout << "a, b: " << a << ", " << b << std::endl;
    swap(a, b);
    std::cout << "SWAPPED" << std::endl;
    std::cout << "a, b: " << a << ", " << b << std::endl;
    return 0;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Reference version is easier because it is more readable.