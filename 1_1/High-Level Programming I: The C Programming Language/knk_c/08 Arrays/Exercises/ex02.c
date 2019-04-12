/* Digit in character form into a subscript */

#include <stdio.h>

int main(void) {
    int digit_count[10] = {0};
    char ch;

    printf("Enter a number: ");

    for (;;) {
        ch = getchar();
        if (ch == '\n')
            break;
        digit_count[ch - '0']++;
    }

    printf("Used digits: \n");
    for (int var = 0; var < (sizeof (digit_count) / sizeof (digit_count[0])); ++var)
        printf("%c : %d\n", var + '0', digit_count[var]);

    return 0;
}
