/* Write macros that, when given a color as an argument,
 * returns its 8-bit color intensities. */

#include <stdio.h>

#define MK_COLOR(RED, GREEN, BLUE) ((long) (RED << 16) | (GREEN << 8) | BLUE)
#define GET_RED(color) (color >> 16)
#define GET_GREEN(color) ((color >> 8) & 255)
#define GET_BLUE(color) (color & 255)

int main(void) {
    unsigned short i, j, k;
    i = 255;
    j = 128;
    k = 8;

    long color = MK_COLOR(i, j, k);
    printf("%ld, %ld, %ld\n", GET_RED(color), GET_GREEN(color), GET_BLUE(color));

    return 0;
}
