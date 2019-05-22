/* a: Use the bitwise operators to write the function swap_bytes */
/* b: Condense the swap_byte function so that its body is a single statement */

#include <stdio.h>

unsigned short swap_bytes(unsigned short i);

int main(void) {
    unsigned short i, j, k;

    printf("Enter a hexaecimal number (up to four digits): ");
    scanf("%hx", &i);
    i = swap_bytes(i);
    printf("Number with bytes swapped: %hx\n", i);

    return 0;
}

unsigned short swap_bytes(unsigned short i) {
    return (i << 8) | (i >> 8);
}
