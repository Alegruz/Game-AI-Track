/* Write the function find_two_largest(a, n, largest, second_largest) */

void find_two_largest(const int *a, int n, int *largest, int *second_largest) {
    *largest = *a;
    *second_largest = *(a + n - 1);
    for (int const *p = a; p < a + n; ++p)
        if (*largest < *p) {
            *second_largest = *largest;
            *largest = *p;
        } else if (*second_largest < *p && *p < *largest)
            *second_largest = *p;
}

