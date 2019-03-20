/* Shows the output produced by following three program fragments. */

#include <stdio.h>

int main(void) {
    int i, j, k;

    /* a */
    i = 5; j =3;
    printf("%d %d\n", i / j, i % j); /* <1 2> */

    /* b */
    i = 2; j = 3;
    printf("%d\n", (i + 10) % j); /* <0> */

    /* c */
    i = 7; j = 8; k = 9;
    printf("%d\n", (i + 10) % k / j); /*  <1> */

    /* d */
    i = 1; j = 2; k = 3;
    printf("%d\n", (i + 5) % (j + 2) / k); /* <0> */


    return 0;
}
