// Write a program to define an array of ten ints.
// Give each element the same value as its position in the array.
#include <cstddef>

int main() {
    constexpr int iarr_size = 10;
    int iarr[iarr_size];    // define an array of ten ints

    for (size_t i = 0; i < iarr_size; ++i)
        iarr[i] = static_cast<int> (i); // give each element the same value as its position in the array

    return 0;
}