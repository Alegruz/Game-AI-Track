/* Reverses the words in a sentence */

#include <stdio.h>
#define SENTENCE_LENGTH 255

int main(void) {
    char sentence[SENTENCE_LENGTH] = {};
    char ch;
    int sentence_index = 0, word_index;

    printf("Enter a sentence: ");
    do {
        ch = getchar();
        sentence[sentence_index] = ch;
        sentence_index++;
    } while (ch != '\n' && ch != '.' && ch != '?' && ch != '!');
    sentence_index--;
    word_index = sentence_index;

    printf("Reversal of sentence: ");
    for (int letter = sentence_index - 1; letter >= 0; --letter) {
        if (sentence[letter] == ' ' || letter == 0) {
            if (letter == 0)
                letter--;
            for (int i = letter + 1; i < word_index; ++i) {
                printf("%c", sentence[i]);
            }
            word_index = letter;
            if (letter >= 0)
                printf(" ");
        }
    }
    printf("%c", sentence[sentence_index]);
    if (sentence[sentence_index] != '\n')
        printf("\n");

    return 0;
}
