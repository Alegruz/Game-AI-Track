/* Counts the number of vowels in a sentence */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char ch;
    int numVowel;

    printf("Enter a sentence: ");

    do {
        ch = getchar();
        switch (toupper(ch)) {
        case 'A': case 'E': case 'I': case 'O': case 'U':
            numVowel++;
            break;
        }
    } while (ch != '\n');

    printf("Your sentence contains %d vowels.\n", numVowel);

    return 0;
}
