/* Checks whether a message is a palindrome */

#include <stdio.h>
#include <ctype.h>

const int message_max_size = 255;

int main(void) {
    char message[message_max_size] = {}, ch;
    int message_size = 0;

    printf("Enter a message: ");
    for (;;) {
        ch = getchar();
        if (ch == '\n')
            break;
        else if ('A' <= toupper(ch) && toupper(ch) <= 'Z') {
//            message[message_size] = toupper(ch);  (a)
            *(message + message_size) = toupper(ch);
            message_size++;
        }
    }

    int palindrome = 0;
//    for (int i = 0; i < message_size && message[i] == message[message_size - 1 - i]; ++i) (a)
    for (char *p = &message[0]; p < message + message_size && *p == *(message + (&message[message_size - 1] - p)); ++p)
        palindrome++;

    if (palindrome >= message_size)
        printf("Palindrome\n");
    else
        printf("Not a palindrome\n");


    return 0;
}
