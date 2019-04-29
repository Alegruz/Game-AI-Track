/* Modify proj14.c from Chapter 8 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int sentence_max_size = 30;
const int word_max_size = 20;

int main(void) {
    char sentence[sentence_max_size][word_max_size + 1] = {{}};
    char ch;

    printf("Enter a sentence: ");
    int sentence_size = 0;
    int marks_size = 0;
    for (; sentence_size < sentence_max_size; ++sentence_size) {
        int word_length = 0;
        for (; word_length < word_max_size && ((ch = getchar()) != '\n' && ch != ' ' && ch != '?' && ch != '!' && ch != '.'); ++word_length) {
            sentence[sentence_size][word_length] = ch;
        }
        for (int i = 0; i < word_max_size && (ch == '.' || ch == '?' || ch == '!'); ++i) {
            sentence[sentence_max_size - 1][i] = ch;
            ch = getchar();
        }

        sentence[sentence_size][word_length] = '\0';
//        sentence[sentence_size][0] = word_length;
        if (ch == '\n')
            break;
    }

    for (int i = sentence_size; 0 <= i; --i) {
        printf("%s ", sentence[i]);
    }

    if (strlen(sentence[sentence_max_size - 1]) > 0)
        printf("\b%s\n", sentence[sentence_max_size - 1]);
    else
        printf("\b\n");

    return 0;
}
