/* Modify read_line function */

#include <stdio.h>
#include <ctype.h>

int read_line(char str[], int n);

int main(void) {
    char read_str[10];

    read_line(read_str, 10);

    puts(read_str);

    return 0;
}

int read_line(char str[], int n) {
    int ch, i = 0;

    /* a */
//    while ((ch = getchar()) != '\n' && ch != EOF)
//        if (i == 0 && isspace(ch))
//            ;
//        else if (i < n)
//            str[i++] = ch;

    /* b */
//    while (!isspace(ch = getchar()))
//        if (i < n)
//            str[i++] = ch;

    /* c */
//    do {
//        ch = getchar()
//        if (i < n)
//            str[i++] = ch;
//    } while (ch != '\n' && ch != EOF);

    /* d */
    for (i = 0; i < n && (ch = getchar()) != '\n'; ++i)
         str[i] = ch;

    str[i] = '\0';
    return i;
}
