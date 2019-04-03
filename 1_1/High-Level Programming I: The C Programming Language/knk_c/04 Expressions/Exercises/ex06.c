/* Computes four implementation-defined behavior expressions */
/* Standard is C99 */

#include <stdio.h>

int main(void) {
    printf("8 %% 5: %d\n", 8 % 5); /* <3> */
    printf("-8 %% 5: %d\n", -8 % 5); /* <-3> */
    printf("8 %% -5: %d\n", 8 % -5); /* <3> */
    printf("-8 %% -5: %d\n", -8 % -5); /* <-3> */
    return 0;
}
