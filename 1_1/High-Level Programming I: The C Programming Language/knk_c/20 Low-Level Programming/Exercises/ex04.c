/* Write a macro that returns a long in which the last
   three bytes contain the red, green, and blue intensities. */

#include <stdio.h>

#define MK_COLOR(RED, GREEN, BLUE) ((long) (RED << 16) | (GREEN << 8) | BLUE)

int main(void) {
    unsigned short i, j, k;
    i = 255;
    j = 128;
    k = 8;

    long color = MK_COLOR(i, j, k);
    printf("%ld, %ld, %ld\n", color >> 16, (color >> 8) & 255, color & 255);

    return 0;
}
