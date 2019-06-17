// Write a program to initialize a vector from an array of ints.
#include <vector>
#include <iterator>

int main() {
    int iarr[10] = {};
    std::vector<int> ivec(std::begin(iarr), std::end(iarr));

    return 0;
}