/* Find a statement not equivalent to other statements */

#include <string.h>

int main(void) {
    char str[] = {'a', 'r', 'r', 'a', 'y'};

    /* a */
    *str = 0;           // 'a' -> '\0'
    /* b */
    str[0] = '\0';      // 'a' -> '\0'
    /* c */
    strcpy(str, "");    // str -> '\0', 'r', 'r', 'a', 'y'
    /* d */
    strcat(str, "");    // str -> "array"

    return 0;
}