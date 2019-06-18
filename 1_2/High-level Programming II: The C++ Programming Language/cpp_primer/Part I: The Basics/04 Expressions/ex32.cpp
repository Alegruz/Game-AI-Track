// Explain the following loop.

int main() {
    constexpr int size = 5;
    int ia[size] = {1,2,3,4,5}; // create an int array with 5 elements, 1, 2, 3, 4, 5
    for (int *ptr = ia, ix = 0;         // for the first element, and number 0
        ix != size && ptr != ia+size;   // up to the last element, and number of the size of the array
        ++ix, ++ptr)   { /* ...   */ }
    return 0;
}