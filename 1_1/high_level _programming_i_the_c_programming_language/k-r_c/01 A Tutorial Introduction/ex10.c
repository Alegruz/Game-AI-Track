#include <stdio.h>

main()
{
    int n = 0;
    char ch;

    while ((ch = getchar()) != EOF) {
        switch (ch) {
        case '\t':
            putchar('\\');
            putchar('t');
            break;
        case '\b':
            putchar('\\');
            putchar('b');
            break;
        case '\\':
            putchar('\\');
            putchar('\\');
            break;
        default:
            putchar(ch);
            break;
        }
    }
}
