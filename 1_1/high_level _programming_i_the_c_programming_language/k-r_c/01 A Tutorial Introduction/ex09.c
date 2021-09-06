#include <stdio.h>

main()
{
    int n = 0;
    char ch;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ') {
            putchar(ch);
            while ((ch = getchar()) != EOF) {
                if (ch != ' ')
                    break;
            }
        }

        putchar(ch);

        if (ch == EOF)
            break;
    }
}
