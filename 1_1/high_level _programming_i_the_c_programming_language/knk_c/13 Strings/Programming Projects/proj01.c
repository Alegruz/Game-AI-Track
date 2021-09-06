/* Finds the smallest and largest in a series of words */

#include <stdio.h>
#include <string.h>

const char *smallest_largest_finder(const char *s, char *_smallest_word, char *_largest_word);

int main(void) {
    char smallest_word[20];
    char largest_word[20];
    char word[20];

    for (;;) {
        printf("Enter word: ");
        gets(word);
        smallest_largest_finder(word, smallest_word, largest_word);
        if (strlen(word) == 4)
            break;
    }

    printf("Smallest word: %s\n", smallest_word);
    printf("Largest word: %s\n", largest_word);

    return 0;
}

const char *smallest_largest_finder(const char *s, char *_smallest_word, char *_largest_word) {
    if (strcmp(s, _smallest_word) <= 0 || strlen(_smallest_word) <= 1)
        strcpy(_smallest_word, s);
    if (strcmp(s, _largest_word) > 0 || strlen(_largest_word) <= 1)
        strcpy(_largest_word, s);

    return s;
}
