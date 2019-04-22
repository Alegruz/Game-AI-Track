/* Modify proj05.c of Chapter 7 */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char ch = ' ';
    const int scrabble_score_sheet[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1,
                                   8, 5, 1, 3, 1, 1, 3, 10, 1,
                                   1, 1, 1, 4, 4, 8, 4, 10};
    int value = 0;

    printf("Enter a word: ");
    while (ch != '\n') {
        ch = getchar();
        if (ch == '\n')
            break;
        else if (toupper(ch) - 'A' < 0 || toupper(ch) - 'A' >= 26)
            printf("Invalid Input\n");
        value += scrabble_score_sheet[toupper(ch) - 'A'];
    }

    printf("Scrabble value: %d\n", value);

    return 0;
}
