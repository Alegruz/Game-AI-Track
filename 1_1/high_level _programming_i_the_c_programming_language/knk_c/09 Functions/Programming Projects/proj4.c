/* Tests whether two words are anagrams using functions */

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define WORD_LENGTH 255

void read_word(int _counts[26]);
bool equal_array(int _counts1[26], int _counts2[26]);

int main(void) {
    int counts1[26] = {};
    int counts2[26] = {};
    int occurrence[26] = {};
    bool is_anagram = false;

    read_word(counts1);
    read_word(counts2);

    printf("The words are ");
    (equal_array(counts1, counts2)) ? printf("") : printf("not ");
    printf("anagrams.\n");

    return 0;
}

void read_word(int _counts[26]) {
    char ch;
    printf("Enter a word: ");
    for (;;) {
        ch = getchar();
        if (ch == '\n')
            break;
        _counts[toupper(ch) - 'A']++;
    }
}

bool equal_array(int _counts1[26], int _counts2[26]) {
    for (int letter = 0; letter < 26; ++letter)
        if (_counts1[letter] != _counts2[letter])
            return false;
    return true;
}
