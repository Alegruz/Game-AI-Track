/* Returns a pointer to a dynamically allocated int array with n members */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *create_array(int n, int initial_value);

int *create_array(int n, int initial_value) {
    int *p = (int *) malloc(n * sizeof (initial_value));

    if (p == NULL) {
        printf("Error: memory full, allocation failed.\n");
        exit(EXIT_FAILURE);
    } else {
        for (int i = 0; i < n; ++i)
            p[i] = initial_value;
        return p;
    }
}
