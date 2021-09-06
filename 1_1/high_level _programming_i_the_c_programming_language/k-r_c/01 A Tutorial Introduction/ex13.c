#include <stdio.h>

#define DONE 1
#define UNDONE 0

main()
{
    char ch;
    int word = DONE, wordLength;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\b') {
            if (word == UNDONE) {
                word = DONE;
                for (int i = 0; i < wordLength; ++i)
                    putchar('=');
                putchar('\n');
                wordLength = 0;
            }
        } else {
            if (word == DONE)
                word = UNDONE;
            wordLength++;
        }
    }
}
