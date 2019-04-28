/* Simplify proj2.c (b) */

#include <stdio.h>
#include <ctype.h>

const int message_max_size = 255;

int main(void) {
    char message[message_max_size] = {}, *p;

    printf("Enter a message: ");
    for (p = message; p < message + message_max_size; ++p) {
        *p = getchar();
        if (*p == '\n')
            break;
        else if (!('A' <= toupper(*p) && toupper(*p) <= 'Z'))
            p--;
    }

    int message_size = --p - message;
    int palindrome = 0;
    for (; p >= message && *p == *(message + (message_size - (p - message))); --p)
        palindrome++;

    if (palindrome >= message_size)
        printf("Palindrome\n");
    else
        printf("Not a palindrome\n");


    return 0;
}
