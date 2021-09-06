/* Find the error in the function duplicate */

#include <string.h>

char *duplicate(const char *p) {
//    char *q;
    char q[strlen(p) + 1];
    for (int i = 0; i < strlen(q) - 1; ++i)
        *q = ' ';
    q[strlen(q) - 1] = '\0';

    strcpy(q, p);
    return q;
}
