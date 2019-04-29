/* Adds up command-line arguments */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int sum = 0;

    if (strcmp(argv[1], "sum") == 0) {
        for (int i = 2; i < argc; ++i)
            sum += atoi(argv[i]);
        printf("Total: %d\n", sum);
    }
    return 0;
}
