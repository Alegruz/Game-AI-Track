/* Simplify proj1.c (b) */

#include <stdio.h>

const int message_size = 255;

int main(void) {
    char message[message_size] = {}, *p;

    printf("Enter a message: ");
    for (p = message; p < message + message_size; ++p) {
        *p = getchar();
        if (*p == '\n')
            break;
    }
    printf("Reversal is: ");
    for (--p; p >= message; --p)
        printf("%c", *p);
    printf("\n");

    return 0;
}
