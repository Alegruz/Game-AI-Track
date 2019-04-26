/* Tests whether two words are anagrams */

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#define WORD_LENGTH 255

int main(void) {
    char ch;
    int occurrence[26] = {};
    bool is_anagram = false;

    printf("Enter first word: ");
    for (;;) {
        ch = getchar();
        if (ch == '\n')
            break;
        occurrence[toupper(ch) - 'A']++;
    }

    printf("Enter second word: ");
    for (;;) {
        ch = getchar();
        if (ch == '\n')
            break;
        occurrence[toupper(ch) - 'A']--;
    }

    for (int letter = 0; letter < 26; ++letter) {
        if (occurrence[letter] != 0) {
            is_anagram = false;
            break;
        }
        is_anagram = true;
    }

    printf("The words are ");
    (is_anagram == true) ? printf("") : printf("not ");
    printf("anagrams.\n");

    return 0;
}
