/* Encrypts a message using a Caesar Cipher */

#include <stdio.h>
#include <stdbool.h>
#define MESSAGE_SIZE 80

int main(void) {
    char message[MESSAGE_SIZE] = {' '};
    char ch;
    bool is_upper = false, is_alpha = false;
    int message_index = 0, shift;

    printf("Enter message to be encrypted: ");

    for (;;) {
        ch = getchar();
        message[message_index] = ch;
        message_index++;
        if (ch == '\n')
            break;
    }

    printf("Enter shift amout (1-25): ");
    scanf("%d", &shift);

    printf("Encrypted message: ");
    for (int letter = 0; letter < message_index; ++letter) {
        if ((message[letter] >= 'a' && message[letter] <= 'z')) {
            is_upper = false;
            is_alpha = true;
        } else if ((message[letter] >= 'A' && message[letter] <= 'Z')) {
            is_upper = true;
            is_alpha = true;
        } else {
            is_alpha = false;
        }
        if (is_alpha == true) {
            message[letter] += shift;
            if (is_upper == false) {
                message[letter] = ((message[letter] - 'a') % 26) + 'a';
            } else {
                message[letter] = ((message[letter] - 'A') % 26) + 'A';
            }
        }
        printf("%c", message[letter]);
    }

    return 0;
}
