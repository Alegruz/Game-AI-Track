// Write a recursive function to print the contents of a vector.
#include <iostream>
#include <vector>

void print_vector(std::vector<int>::iterator begin, std::vector<int>::iterator end);

int main() {

    std::vector<int> iv(20, 3);

    print_vector(iv.begin(), iv.end());

    return 0;
}

void print_vector(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    if (begin != end) {
        std::cout << *begin++;
        print_vector(begin, end);
    }

    return;
}
