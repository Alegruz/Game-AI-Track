/* Modify proj10.c from Chapter 7 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int compute_vowel_count(const char *sentence);

int main(void)
{
    char sentence[100];
    int num_vowel, i;

    printf("Enter a sentence: ");

    for (i = 0; i < 100 && (sentence[i] = getchar()) != '\0' && sentence[i] != '\n'; ++i)
        ;
    sentence[i] = '\0';
    num_vowel = compute_vowel_count(sentence);

    printf("Your sentence contains %d vowels.\n", num_vowel);

    return 0;
}

int compute_vowel_count(const char *sentence) {
    int num_vowel = 0;
    for (int i = 0; i < strlen(sentence); ++i)
        switch (toupper(*(sentence + i))) {
        case 'A': case 'E': case 'I': case 'O': case 'U':
            num_vowel++;
            break;
        default:
            break;
        }
    return num_vowel;
}
