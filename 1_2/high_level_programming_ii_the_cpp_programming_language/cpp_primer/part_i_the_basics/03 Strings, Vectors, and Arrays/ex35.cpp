// Using pointers, write a program to set the elements in an array to zero.
#include <cstddef>

int main() {
    constexpr int arr_size = 10;
    int iarr[arr_size];
 
    for (int *i = iarr; i != iarr + arr_size; ++i)
        *i = 0;

    return 0;
}