/* Write a function censor */

#include <stdio.h>
#include <string.h>

char *censor(char *s);

int main(void) {
    char text[] = "food fool";

    printf("%s\n", censor(text));

    return 0;
}

char *censor(char *s) {
    // char *p = s;
    // char foo[4] = {};
    // int foo_index = 0;

    // while (*p) {
    //     if (*p == 'f' || *p == 'o')
    //         foo[foo_index++] = *p;
    //     if (foo_index >= 2) {
    //         foo[3] = '\0';
    //         if (strcmp(foo, "foo") == 0) {
    //             *p = *(p - 1) = *(p - 2) = 'x';
    //             strcpy(foo, "   ");
    //             foo_index = 0;
    //         }
    //     }
    //     *p++;
    // }
    char *p = s;

    while (*p) {
        if (*p == 'f' && *(p + 1) == 'o' && *(p + 2) == 'o')
            *p = *(p + 1) = *(p + 2) = 'x';
        *p++;
    }

    return s;
}
