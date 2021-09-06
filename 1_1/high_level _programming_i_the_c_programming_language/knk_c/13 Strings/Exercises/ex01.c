/* Explain why some of the following calls don't work */

#include <stdio.h>

int main(void) {
    /* a */
    printf("%c", '\n');
    /* b */
//    printf("%c", "\n"); char <- const char * (string literal)
    /* c */
//    printf("%s", '\n'); const char * (string literal) <- char
    /* d */
    printf("%s", "\n");
    /* e */
//    printf('\n'); argument must be const char *
    /* f */
    printf("\n");
    /* g */
    putchar('\n');
    /* h */
//    putchar("\n"); argument must be int (char)
    /* i */
//    puts('\n'); argument must be const char *
    /* j */
    puts("\n");
    /* k */
    puts("");
    return 0;
}
