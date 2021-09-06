#include <stdio.h>

#define DONE 1
#define UNDONE 0

main()
{
    char ch;
    int chList[127] = {0};

    while ((ch = getchar()) != EOF) {
        chList[ch]++;
    }

    for (int i = 0; i < 127; ++i)
        printf("chList[%-3d]: %d\n", i, chList[i]);
}
