// Write a program to create a vector with ten int elements.
// Using an iterator, assign each element a value that is twice its current value.
// Test your program by printing the vector.
#include <vector>
#include <iostream>

int main() {
    std::vector<int> ivec(10, 2);   // create a vector with ten int elements

    for (auto iter = ivec.begin(); iter != ivec.end(); ++iter) {    // use an iterator
        *iter *= 2; // assign each element a value that is twice its current value
        std::cout << *iter << " ";  // test your program
    }
    std::cout << std::endl;

    return 0;
}