/* Declares an array with 40 fibonacci numbers */

#include <stdio.h>

#define N 40

int main(void) {
    int fib_numbers[N] = {0, 1};

    for (int i = 2; i < N; ++i) {
        fib_numbers[i] = fib_numbers[i - 1] + fib_numbers[i - 2];
    }

    for (int i = 0; i < N; ++i) {
        if (!(i % 3))
            printf("\n");
        printf("fib_numbers[%-2d] = %-8d ", i, fib_numbers[i]);
    }

    printf("\n");

    return 0;
}
