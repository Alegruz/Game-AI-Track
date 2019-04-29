/* Modify proj15.c from Chapter 8 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MESSAGE_MAX_SIZE 80

void encrypt(char *message, int shift);

int main(void) {
    char message[MESSAGE_MAX_SIZE] = {};
    int shift;

    printf("Enter message to be encrypted: ");

    int message_size = 0;
    for (; message_size < MESSAGE_MAX_SIZE && ((message[message_size] = getchar()) != '\n'); ++message_size)
        ;
    message[message_size] = '\0';
    printf("%s\n", message);

    printf("Enter shift amout (1-25): ");
    scanf("%d", &shift);

    encrypt(message, shift);

    printf("Encrypted message: %s\n", message);

    return 0;
}

void encrypt(char *message, int shift) {
    for (; *message != '\0'; ++message) {
        if ('a' <= *message && *message <= 'z')
            *message = ((*message + shift - 'a') % 26) + 'a';
        else if ('A' <= *message && *message <= 'Z')
            *message = ((*message + shift - 'A') % 26) + 'A';
    }
}
