/* Finds the statement that is not equivalent to other two */

#include <stdio.h>

int main(void)
{
    int i;

    /* a */
    i = 10;
    while (i < 10) {
        printf("%d ", i++);
    } printf("\n"); /* <> */

    /* b */
    i = 10;
    for (; i < 10;) {
        printf("%d ", i++);
    } printf("\n"); /* <> */

    /* c */
    i = 10;
    do {
        printf("%d ", i++);
    } while (i < 10); printf("\n"); /* <10> */

    return 0;
}
