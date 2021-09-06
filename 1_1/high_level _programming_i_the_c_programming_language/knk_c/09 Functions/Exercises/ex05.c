/* Write a function num_digits(n) */

#include <stdio.h>

int num_digits(int n);

int main(void) {
    int n;
    printf("Digit Calculator\nEnter a number: ");
    scanf("%d", &n);

    printf("%d has %d digit(s).\n", n, num_digits(n));

    return 0;
}

int num_digits(int n) {
    int digit = 0;
    
    do {
        n /= 10;
        digit++;
    } while (n > 0);

    return digit;
}