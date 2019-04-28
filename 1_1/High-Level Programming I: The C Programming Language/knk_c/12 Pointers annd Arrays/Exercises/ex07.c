/* Write the function search(a, n, key) */

#include <stdbool.h>

bool search(const int a[], int n, int key);

bool search(const int a[], int n, int key) {
    for (int const *p = &a[0]; p < a + n; ++p)
        if (*p == key)
            return true;
    return false;
}
