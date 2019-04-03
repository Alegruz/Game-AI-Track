/* Justify whether i++ or ++i is equivalent to (i += 1) */

#include <stdio.h>

int main(void) {
    int i = 1;

    printf("i: %d\n", i);
    printf("i++: %d, i: %d\n", i++, i); /* <i++: 1, i: 2> */
    i--;
    printf("++i: %d, i: %d\n", ++i, i); /* <++i: 2, i: 2> */
    i--;
    printf("i += 1: %d, i: %d\n", (i += 1), i); /* <i += 1: 2, i: 2> */
    /* ++i is equivalent to i += 1 */

    return 0;
}
