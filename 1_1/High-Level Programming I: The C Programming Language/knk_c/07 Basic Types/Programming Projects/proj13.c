/* Calculates average word length for a sentence */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char ch, capCh;
    int word = 0, totalWords = 0;
    float average;
    printf("Enter a sentence: ");

    for (;;) {
        ch = getchar();
        capCh = toupper(ch);
        if (capCh >= 'A' && capCh <= 'Z' || ch == '-' || ch == '.') {
            word++;
        } else if (ch == ' ' || ch == '\n') {
            average += word;
            totalWords++;
            word = 0;
            if (ch == '\n') {
                average /= totalWords;
                break;
            }
        }
    }

    printf("Average word length: %.1f\n", average);

    return 0;
}
