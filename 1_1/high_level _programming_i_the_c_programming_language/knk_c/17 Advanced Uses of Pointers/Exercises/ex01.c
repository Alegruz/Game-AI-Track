/* Write a function named my_malloc */

#include <stdio.h>
#include <stdlib.h>

void *my_malloc(int n);

void *my_malloc(int n) {
    void *p = malloc(n);
    if (p == NULL) {
        printf("Error: memory full\n");
        exit(EXIT_FAILURE);
    } else
        return p;
}
