/* Shows the output produced by following four program fragments. */

#include <stdio.h>

int main(void) {
    int i, j, k;

    /* a */
    i = 1;
    printf("%d ", i++ - 1); /* <0> */
    printf("%d\n", i); /* <2> */

    /* b */
    i = 10; j = 5;
    printf("%d ", i++ - ++j); /* <4> */
    printf("%d %d\n", i, j); /* <11, 6> */

    /* c */
    i = 7; j = 8;;
    printf("%d ", i++ - --j); /* <0> */
    printf("%d %d\n", i, j); /* <8, 7> */

    /* d */
    i = 3; j = 4; k = 5;
    printf("%d ", i++ - j++ + --k); /* <3> */
    printf("%d %d %d\n", i, j, k); /* <4 5 4> */

    return 0;
}
