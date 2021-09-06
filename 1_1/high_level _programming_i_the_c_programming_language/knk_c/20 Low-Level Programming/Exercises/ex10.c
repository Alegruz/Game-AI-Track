/* Write the function reverse_bits(n) */

#include <stdio.h>
#include <string.h>

unsigned int reverse_bits(unsigned int n);
char *byte_to_binary_str(int byte);
void print_int_bits(int value);

int main(void) {
    printf("%d\n", sizeof (unsigned int));
    /* unsigned int n = 0xff00ff00; */
    unsigned int n = 0xfabfe74d;
    printf("Original: ");
    print_int_bits(n);
    /* n = reverse_bits(n); */
    n = reverse_bits(n);
    printf("Reversed: ");
    print_int_bits(n);
}

unsigned int reverse_bits(unsigned int n) {
    unsigned int reverse = 0;
    for (unsigned int i = 8 * sizeof (unsigned int); i > 0; --i)
        reverse |= ((n >> (i - 1)) & 1) << (8 * sizeof(unsigned int) - i);

    return reverse;
}

char *byte_to_binary_str(int byte) {
    static char bit_string[9];
    bit_string[0] = '\0';

    int mask;
    for (mask = 0x80; mask > 0; mask >>= 1) {
        /* Check if the mask bit is set */
        strcat(bit_string, byte & mask ? "1" : "0");
    }

    return bit_string;
}

void print_int_bits(int value)
{
    static int i;

    for (i = sizeof(int) - 1; i >= 0; i--) {
        printf("%s ", byte_to_binary_str(value >> (i * 8)));
    }
    printf("\n");
}
