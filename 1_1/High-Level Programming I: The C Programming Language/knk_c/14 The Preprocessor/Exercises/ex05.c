/* Shows the output produced by each of the following program fragments */

#include <stdio.h>
#include <string.h>

#define TOUPPER(c) ('a'<=(c)&&(c)<='z'?(c)-'a'+'A':(c))

int main(void) {
    char s[10] = {};

    /* a */
    strcpy(s, "abcd");
    int i = 0;
    putchar(TOUPPER(s[++i]));
/*  putchar(('a'<=(s[++i])&&(s[++i])<='z'?(s[++i])-'a'+'A':(s[++i])));
 *  putchar(('a'<=(s[1])&&(s[2])<='z'?(s[3])-'a'+'A':(s[++i])));
 *  putchar(('a'<=('b')&&('c')<='z'?('d')-'a'+'A':(s[++i])));
 *  >> D
 */

    /* b */
    strcpy(s, "0123");
    i = 0;
    putchar(TOUPPER(s[++i]));
/*  putchar(('a'<=(s[++i])&&(s[++i])<='z'?(s[++i])-'a'+'A':(s[++i])));
 *  putchar(('a'<=(s[1])&&(s[++i])<='z'?(s[++i])-'a'+'A':(s[2])));
 *  putchar(('a'<=('1')&&(s[++i])<='z'?(s[++i])-'a'+'A':('2')));
 *  >> 2
 */

    return 0;
}
