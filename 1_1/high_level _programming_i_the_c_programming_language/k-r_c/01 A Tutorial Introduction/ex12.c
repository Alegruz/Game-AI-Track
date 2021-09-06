#include <stdio.h>

#define DONE 1
#define UNDONE 0

main()
{
    int word = DONE;
    char ch;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\b') {
            if (word == UNDONE) {
                putchar('\n');
                word = DONE;
            }
        }

        else {
            putchar(ch);
            word = UNDONE;
        }
    }
}
