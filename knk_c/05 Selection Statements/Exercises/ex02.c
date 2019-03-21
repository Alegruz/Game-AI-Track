/* Shows the output of each program fragments */

#include <stdio.h>

int main(void) {
    int i, j, k;

    /* a */
    i = 10; j = 5;
    printf("%d\n", !i < j); /* <1> */

    /* b */
    i = 2; j = 1;
    printf("%d\n", !!i + !j); /* <1> */

    /* c */
    i = 5; j = 0; k = -5;
    printf("%d\n", i && j || k); /* <1> */

    /* d */
    i = 1; j = 2; k = 3;
    printf("%d\n", i < j || k); /* <1> */

    return 0;
}
