/* Answer to following questions */

#include <stdio.h>

#define DOUBLE(x) 2*x

int main(void) {
    printf("(a) DOUBLE(1+2) = %d\n", DOUBLE(1+2));
    printf("(b) 4/DOUBLE(2) = %.2lf\n", 4 / DOUBLE(2));
    printf("(c) #define DOUBLE(x) 2*(x)\n");

    return 0;
}
