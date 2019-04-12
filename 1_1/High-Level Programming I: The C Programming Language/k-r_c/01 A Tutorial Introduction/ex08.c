#include <stdio.h>

main()
{
    int n = 0;
    char ch;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\t' || ch =='\n')
            n++;
        printf("%d\n", n);
    }
}
