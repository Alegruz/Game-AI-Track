/* Modify proj2.c from Chapter 12 */

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

const int message_max_size = 255;

bool is_palindrome(const char *message);

int main(void) {
    char message[message_max_size] = {}, ch;

    printf("Enter a message: ");
    int message_size = 0;
    for (; message_size < message_max_size && (message[message_size] = getchar()) != '\n'; ++message_size)
        if ('A' <= toupper(message[message_size]) && toupper(message[message_size]) <= 'Z')
            message[message_size] = toupper(message[message_size]);
    message[message_size] = '\0';

    if (is_palindrome(message))
        printf("Palindrome\n");
    else
        printf("Not a palindrome\n");


    return 0;
}

bool is_palindrome(const char *message) {
    int palindrome = 0;
    for (char const *p = message; *p != 0 && *p == *(message + strlen(message) - 1 - (p - message)); ++p)
        palindrome++;
    return palindrome == strlen(message);
}
