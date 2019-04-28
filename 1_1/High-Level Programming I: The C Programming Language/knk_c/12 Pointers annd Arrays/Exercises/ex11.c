/* Modify the find_largest function */

int find_largest(int *a, int n) {
    int max = *a;
    for (int *p = a; p < a + n; p++)
        if (*p > max)
            max = *p;
    return max;
}
