/* Prints a table of squares and asks user whether to continue */

#include <stdio.h>

int main(void)
{
    int i, n;
    char ch;

    printf("This program prints a table of squares.\n");
    printf("Enter number of entries in table: ");
    scanf("%d", &n);
    getchar();

    for (i = 1; i <= n; i++) {
        printf("%10d%10d\n", i, i * i);
        if (!(i % 24)) {
            printf("Press Enter to continue...");
            ch = ' ';
            do {
                ch = getchar();
            } while (!(ch == '\n'));
        }
    }

    return 0;
}
