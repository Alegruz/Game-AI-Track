/* Write a function gcd(m, n) */

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
    int gcd;
    for (int i = m; i > 0; --i) {
        if (m % i == 0 && n % i == 0) {
            gcd = i;
            break;
        }
    }
    return gcd;
}