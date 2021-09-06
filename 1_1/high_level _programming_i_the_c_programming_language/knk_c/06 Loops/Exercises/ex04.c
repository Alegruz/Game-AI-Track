/* Finds the statement that is not equivalent to other two */

#include <stdio.h>

int main(void)
{
    int i;

    /* a */
    for (i = 0; i < 10; i++) {
        printf("%d ", i);
    } printf("\n"); /* <0 1 2 3 4 5 6 7 8 9> */

    /* b */
    for (i = 0; i < 10; ++i) {
        printf("%d ", i);
    } printf("\n"); /* <0 1 2 3 4 5 6 7 8 9> */

    /* c */
    for (i = 0; i++ < 10; ) {
        printf("%d ", i);
    } printf("\n"); /* <1 2 3 4 5 6 7 8 9 10> */

    return 0;
}
