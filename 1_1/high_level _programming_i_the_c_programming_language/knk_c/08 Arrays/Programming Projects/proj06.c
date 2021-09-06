/* B1FF translator */

#include <stdio.h>

int main(void) {
    char ch;
    char message[255];
    const char translator[][2] = {{'A', '4'}, {'B', '8'}, {'E', '3'}, {'I', '1'}, {'O', '0'}, {'S', '5'}};
    unsigned short message_index = 0;

    printf("Enter message: ");

    for (;;) {
        ch = getchar();
        if (ch == '\n')
            break;
        else if (ch >= 'a' && ch <= 'z')
            ch += 'A' - 'a';
        message[message_index] = ch;
        message_index++;
    }

    printf("In B1FF-speak: ");
    for (int i = 0; i < message_index; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (message[i] == translator[j][0])
                message[i] = translator[j][1];
        }
        printf("%c", message[i]);
    }
    for (int i = 0; i < 10; ++i)
        printf("!");
    printf("\n");

    return 0;
}
