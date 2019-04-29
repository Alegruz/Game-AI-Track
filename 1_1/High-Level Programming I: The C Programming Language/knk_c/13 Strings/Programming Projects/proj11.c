/* Modify proj13.c from Chapter 7 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

double compute_average_word_length(const char *sentence);

int main(void)
{
    char sentence[100];
    printf("Enter a sentence: ");

    int i = 0;
    for (; i < 100 && (*(sentence + i) = getchar()) != '\n'; ++i)
        ;
    *(sentence + i) = '\0';

    printf("Average word length: %.1f\n", compute_average_word_length(sentence));

    return 0;
}

double compute_average_word_length(const char *sentence) {
    char const *p = sentence;
    char cap_ch;
    double word = 0.0, total_words = 0.0, average = 0.0;

    for (; *p != 0; ++p) {
        cap_ch = toupper(*p);
        if (cap_ch >= 'A' && cap_ch <= 'Z' || *p == '-' || *p == '.')
            word++;
        if (*p == ' ' || *p == '\n' || *(p + 1) == 0) {
            average += word;
            total_words++;
            word = 0;
            if (*(p + 1) == '\0') {
                average /= total_words;
                break;
            }
        }
    }
    return average;
}
