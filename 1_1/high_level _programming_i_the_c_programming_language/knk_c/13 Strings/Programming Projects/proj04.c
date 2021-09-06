/* Echoes its command-line arguments in reverse order */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "reverse") == 0) {
        for (int i = argc - 1; 1 < i; --i)
            printf("%s ", argv[i]);
        printf("\n");
    }
    return 0;
}
