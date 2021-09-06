// Identify the indexing errors in the following code:
#include <cstddef>

int main() {
    constexpr size_t array_size = 10;
    int ia[array_size]; // uninitialized. undefined values.
    for (size_t ix = 1; ix <= array_size; ++ix) // array index starts at 0 and ends at size - 1. indexing error.
        ia[ix] = ix;
    return 0;
}