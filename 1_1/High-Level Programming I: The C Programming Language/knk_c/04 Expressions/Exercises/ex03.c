/* Computes four implementation-defined behavior expressions */
/* Standard is C89 */

#include <stdio.h>

int main(void) {
    printf("8 / 5: %d\n", 8 / 5); /* <1> */
    printf("-8 / 5: %d\n", -8 / 5); /* <-1> or <-2> */
    printf("8 / -5: %d\n", 8 / -5); /* <-1> or <-2> */
    printf("-8 / -5: %d\n", -8 / -5); /* <1> or <2> */
    return 0;
}
