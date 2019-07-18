/* Prints the reversal of the message */

#include <stdio.h>

const int message_size = 255;

int main(void) {
    char message[message_size] = {}, ch;
    int message_index = 0;

    printf("Enter a message: ");
    for (;;) {
        ch = getchar();
        if (ch == '\n')
            break;
//        message[message_index] = ch; (a)
        *(message + message_index) = ch;
        message_index++;
    }

    printf("Reversal is: ");
//    for (int i = message_index - 1; i >= 0; --i)  (a)
//        printf("%c", message[i]);                 (a)
    for (char *p = &message[message_index - 1]; p >= &message[0]; --p)
        printf("%c", *p);
    printf("\n");

    return 0;
}
