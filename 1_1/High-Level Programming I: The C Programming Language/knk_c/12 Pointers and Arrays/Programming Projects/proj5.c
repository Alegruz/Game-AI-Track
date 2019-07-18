/* Modify proj14.c from chapter 8 */

#include <stdio.h>

#define SENTENCE_LENGTH 255

int main(void) {
    char sentence[SENTENCE_LENGTH] = {}, *p;

    printf("Enter a sentence: ");
    for (p = sentence; p < sentence + SENTENCE_LENGTH; ++p) {
        *p = getchar();
        if (*p == '\n')
            break;
    }

    int word_length = 0;
    int ending = 0;
    int size = p-- - sentence;
    printf("Reversal of sentence: ");
    for (; p >= sentence; --p) {
        if (*p == '!' || *p == '?' || *p =='.') {
            ending++;
            continue;
        } else if (*p == ' ' || p == sentence) {
            for (char *q = p + (p != sentence); q <= p + word_length; ++q)
                printf("%c", *q);
            word_length = 0;
            p == sentence ? : printf(" ");
        } else {
            word_length++;
        }
    }
    for (char *q = (sentence + size - ending); q <= sentence + size; ++q)
        printf("%c", *q);

    return 0;
}
