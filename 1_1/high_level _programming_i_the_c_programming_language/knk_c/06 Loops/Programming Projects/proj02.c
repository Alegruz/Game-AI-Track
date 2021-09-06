/* Calculates the greatest commond divisor of two integers */

#include <stdio.h>

int main(void) {
    int i, x, y, gcd;

    printf("Enter two integers: ");
    scanf("%d %d", &x, &y);

//    for (i = x; i > 0; --i) {
//        if (x % i == 0 && y % i == 0) {
//            gcd = i;
//            break;
//        }
//    }

    while (y) {
        i = x % y;
        x = y;
        y = i;
    }

    gcd = x;

    printf("Greatest common divisor: %d\n", gcd);

    return 0;
}
