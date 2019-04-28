/* Search the entire temperatures array for the value 32 */

#include <stdio.h>
#include <stdbool.h>

bool search(const int a[], int n, int key);

int main(void) {
    int temperatures[7][24];

    printf("Is 32 in the record? %d\n", search(*temperatures, 7 * 24, 32));

    return 0;
}

bool search(const int a[], int n, int key) {
    for (int const *p = &a[0]; p < a + n; ++p)
        if (*p == key)
            return true;
    return false;
}
