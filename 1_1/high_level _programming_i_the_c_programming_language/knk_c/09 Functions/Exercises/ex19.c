/* Trace the execution of following function */

#include <stdio.h>

void pb(int n);

int main(void) {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);

    pb(n);

    return 0;
}

void pb(int n) {
    printf("FUNCTION EXECUTED. VALUE OF n: %d, BINARY VALUE OF n: %d\n", n, n % 2);
    if (n != 0) {
        pb(n / 2);
        putchar('0' + n % 2);
    }
}
