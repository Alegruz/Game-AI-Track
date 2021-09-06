/* Write a function digit(n, k) */

#include <stdio.h>

int digit(int n, int k);

int main(void) {
    int n, k;
    printf("Digit Finder\nEnter a number and an index: ");
    scanf("%d%d", &n, &k);

    printf("The digit in index %d is %d.\n", k, digit(n, k));

    return 0;
}

int digit(int n, int k) {
    for (int i = 1; i < k; ++i) {
        if (n < 0)
            return 0;
        n /= 10;
    }
    return n % 10;
}
