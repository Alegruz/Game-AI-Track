/* Explain the following macro */

#include <stdio.h>

#define M(x,y) ((x)^=(y), (y)^=(x), (x)^=(y))

/* ex) M(2, 1)
   010 ^ 001 = 011
   x = 3, y = 1
   001 ^ 011 = 010
   x = 3, y = 2
   011 ^ 010 = 001
   x = 1, y = 2   */

int main(void) {
    unsigned i, j, k;

    i = 23;
    j = 3;

    M(i, j);

    printf("i: %d, j: %d\n", i, j); /* 3, 23 */

    return 0;
}
