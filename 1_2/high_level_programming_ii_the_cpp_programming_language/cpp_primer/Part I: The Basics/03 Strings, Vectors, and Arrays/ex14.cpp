// Write a program to read a sequence of ints from cin and store those values in a vector.
#include <iostream>
#include <vector>

int main() {
    int i;
    std::vector<int> ivec;
    while (std::cin >> i)   // read a sequence of ints
        ivec.push_back(i);  // store the value in a vector

    return 0;
}