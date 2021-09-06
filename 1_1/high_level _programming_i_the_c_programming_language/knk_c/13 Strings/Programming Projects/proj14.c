/* Modify proj16.c from Chapter 8 */

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define WORD_LENGTH 255

bool are_anagrams(const char *word1, const char *word2);

int main(void) {
    char word1[WORD_LENGTH] = {}, word2[WORD_LENGTH] = {};
    bool is_anagram;

    printf("Enter first word: ");
    int word1_length = 0;
    for (; word1_length < WORD_LENGTH && (word1[word1_length] = getchar()) != '\n'; ++word1_length)
        ;
    word1[word1_length] = '\0';

    printf("Enter second word: ");
    int word2_length = 0;
    for (; word2_length < WORD_LENGTH && (word2[word2_length] = getchar()) != '\n'; ++word2_length)
        ;
    word2[word2_length] = '\0';

    printf("The words are ");
    are_anagrams(word1, word2) ? printf("") : printf("not ");
    printf("anagrams.\n");

    return 0;
}

bool are_anagrams(const char *word1, const char *word2) {
    int occurrence[26] = {};
    if (strlen(word1) != strlen(word2))
        return false;
    char const *p = word1, *q = word2;
    for (; (*p) * (*q) != 0; ++p, ++q) {
        occurrence[toupper(*p) - 'A']++;
        occurrence[toupper(*q) - 'A']--;
    }

    for (int i = 0; i < 26; ++i)
        if (occurrence[i] != 0)
            return false;
    return true;
}
