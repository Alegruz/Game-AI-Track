/* Modify proj1.c from Chapter 12 */

#include <stdio.h>
#include <string.h>

const int message_max_size = 255;

void reverse(char *message);

int main(void) {
    char message[message_max_size] = {}, ch;
    int message_index = 0;

    printf("Enter a message: ");
    int message_size = 0;
    for (; message_size < message_max_size && (message[message_size] = getchar()) != '\n'; ++message_size)
        ;
    message[message_size] = '\0';

    reverse(message);
    printf("Reversal is: %s\n", message);

    return 0;
}

void reverse(char *message) {
    for (int i = 0; i < strlen(message) / 2; ++i) {
        char temp = message[i];
        message[i] = message[strlen(message) - 1 - i];
        message[strlen(message) - 1 - i] = temp;
    }
}
