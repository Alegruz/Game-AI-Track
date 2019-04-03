/* Give the value of i and j after each following expression statements */

#include <stdio.h>

int main(void) {
    int i = 1, j = 2;

    /* a */
    i += j;
    printf("i += j, %d %d\n", i, j); /* <3 2> */


    /* b */
    i = 1; j = 2;
    i--;
    printf("i--, %d %d\n", i, j); /* <0 2> */


    /* c */
    i = 1; j = 2;
    i * j / i;
    printf("i * j / i, %d %d\n", i, j); /* <1 2> */


    /* d */
    i = 1; j = 2;
    i % ++j;
    printf("i %% ++j, %d %d\n", i, j); /* <1 3> */

    return 0;
}
