/* Uses dynamic storage allocation to create a copy of a string */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *duplicate(char *str);

char *duplicate(char *str) {
    char *p = (char *) malloc(strlen(str + 1) * sizeof (*str));
    if (p == NULL) {
        printf("Error: memory full. duplication failed\n");
        exit(EXIT_FAILURE);
    } else {
        strcpy(p, str);
        return p;
    }
}
