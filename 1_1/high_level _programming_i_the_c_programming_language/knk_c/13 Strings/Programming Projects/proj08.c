/* Modify proj05.c from Chapter 7 */

#include <stdio.h>
#include <ctype.h>

int compute_scrabble_value(const char *word);

int main(void)
{
    char ch = 0, word[20];
    int value = 0, i = 0;

    printf("Enter a word: ");
    for (; i < 20 && (word[i] = getchar()) != '\n'; ++i)
        ;
    word[i] = '\0';
    value = compute_scrabble_value(word);

    printf("Scrabble value: %d\n", value);

    return 0;
}

int compute_scrabble_value(const char *word) {
    int value = 0;
    while (*word != '\0') {
        switch (toupper(*word++)) {
        case 'A': case 'E': case 'I': case 'L': case 'N': case 'O': case 'R': case 'S': case 'T': case 'U':
            value += 1; break;
        case 'D': case 'G':
            value += 2; break;
        case 'B': case 'C': case 'M': case 'P':
            value += 3; break;
        case 'F': case 'H': case 'V': case 'W': case 'Y':
            value += 4; break;
        case 'K':
            value += 5; break;
        case 'J': case 'X':
            value += 8; break;
        case 'Q': case 'Z':
            value += 10; break;
        case '\n':
            continue;
        default:
            printf("Invalid Input"); break;
        }
    }
    return value;
}
