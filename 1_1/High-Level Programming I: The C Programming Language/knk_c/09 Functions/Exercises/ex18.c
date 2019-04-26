/* Write a recursive version of gcd */

#include <stdio.h>

int gcd(int m, int n);

int main(void) {
    int m, n;

    printf("GCD Calculator\nEnter two integers: ");
    scanf("%d%d", &m, &n);

    printf("The gcd of %d and %d is %d.\n", m, n, gcd(m, n));

    return 0;
}

int gcd(int m, int n) {
    return n == 0 ? m : gcd(n, m % n);
}
