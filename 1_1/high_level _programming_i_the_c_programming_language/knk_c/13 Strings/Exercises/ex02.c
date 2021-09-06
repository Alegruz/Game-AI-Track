/* Tell whether following statements are legal and show their output */

#include <stdio.h>

int main(void) {
    char *p = "abc";

    /* a */
//    putchar(p); int (char) <- const char *
    /* b */
    putchar(*p);    // a
    /* c */
    puts(p);        // abc\n
    /* d */
//    puts(*p); const char * <- char

    return 0;
}
