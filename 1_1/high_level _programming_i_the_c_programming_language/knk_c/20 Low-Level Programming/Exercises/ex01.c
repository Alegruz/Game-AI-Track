/* Show the output produced by each of the following program fragments */

#include <stdio.h>

int main(void) {
    unsigned i, j, k;

    /* a */
    i = 8; j = 9;
    printf("a: %d\n", i >> 1 + j >> 1); /* 0 */

    /* b */
    i = 1;
    printf("b: %d\n", i & ~i); /* 0 */

    /* c */
    i = 2; j = 1; k = 0;
    printf("c: %d\n", ~i & j ^ k);  /* 1 */

    /* d */
    i = 7; j = 8; k = 9;
    printf("d: %d\n", i ^ j & k);   /* 15 */

    return 0;
}
