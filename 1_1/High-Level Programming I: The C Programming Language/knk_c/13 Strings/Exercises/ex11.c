/* Modify strcmp(s, t) */

#include <stdio.h>

int _strcmp(char *s, char *t);

int main(void) {
    char s[] = "damn0";
    char t[] = "damn1";

    printf("Result: %d\n", _strcmp(s, t) < 0);

    return 0;
}

int _strcmp(char *s, char *t) {
    char *_s = s, *_t = t;

    for (; *_s == *_t; *_s++, *_t++) {
        if (*_s == 0)
            return 0;
    }

    return *_s - *_t;
}
