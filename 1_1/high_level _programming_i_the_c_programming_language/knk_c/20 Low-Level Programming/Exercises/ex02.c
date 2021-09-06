/* Describe a simple way to "toggle" a bit (change it
   from 0 to 1 or from 1 to 0). Illutrate the technique
   by writing a statement that toggles bit 4 of the
   variable i. */

#include <stdio.h>

int main(void) {
    unsigned i, j, k;

    i = 23;  /* 010111 */
    j = i ^ (1 << 3);   /* i ^ (1 << (bit_pos - 1)) */
                        /* i == 011111 == 31 */
    printf("%d\n", j);  /* 31 */

    return 0;
}
