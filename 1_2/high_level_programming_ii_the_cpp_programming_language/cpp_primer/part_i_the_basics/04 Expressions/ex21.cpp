// Write a program to use a conditional operator
// to find the elements in a vector<int> that have odd value and double the value of each such element.
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};

    for (auto &elem : v) {
        elem *= (elem % 2 == 1) ? 2 : 1;
        std::cout << elem << std::endl;
    }

    return 0;
}