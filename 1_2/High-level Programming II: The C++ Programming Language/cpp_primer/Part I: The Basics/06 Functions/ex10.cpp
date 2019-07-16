// Using pointers, write a function to swap the values of two ints.
// Test the function by calling it and printing the swapped values.
#include <iostream>

void swap(int *a, int *b);

int main() {
    int a = 3, b = 4;

    std::cout << "a, b: " << a << ", " << b << std::endl;
    swap(&a, &b);
    std::cout << "SWAPPED" << std::endl;
    std::cout << "a, b: " << a << ", " << b << std::endl;
    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}