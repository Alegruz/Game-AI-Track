/* Write the function count_ones(ch) */

#include <stdio.h>

int count_ones(unsigned char ch);

int main(void) {
    unsigned char ch;
    ch = 127;
    printf("one bits in %d: %d\n", ch, count_ones(ch));

    return 0;
}

/* a
int count_ones(unsigned char ch) {
    int count = 0;
    for (unsigned int i = 0; i < sizeof (unsigned char) * 8; ++i) {
        if (((ch >> i) & 1) == 1)
            count++;
    }
    return count;
}
*/

/* b */
int count_ones(unsigned char ch) {
    return ((ch >> 7) & 1) +
            ((ch >> 6) & 1) +
            ((ch >> 5) & 1) +
            ((ch >> 4) & 1) +
            ((ch >> 3) & 1) +
            ((ch >> 2) & 1) +
            ((ch >> 1) & 1) +
            (ch & 1);
}
