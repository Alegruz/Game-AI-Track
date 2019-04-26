/* Modify proj11.c of Chapter 7 */

#include <stdio.h>
#include <ctype.h>

#define LAST_NAME_SIZE 20

int main(void)
{
    char name_ch;
    char last_name[LAST_NAME_SIZE] = {};
    int index = 0;

    printf("Enter a first and last name: ");

    last_name[index] = getchar();
    printf("You entered the name: ");
    index++;
    for (;;) {
        last_name[index] = getchar();
        if (last_name[index] == ' ') break;
        index++;
    }

    for (;;) {
        name_ch = getchar();
        if (name_ch == '\n') break;
        printf("%c", name_ch);
    }

    printf(", %c.\n", last_name[0]);

    return 0;
}
