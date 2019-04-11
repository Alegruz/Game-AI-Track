/* Abbreviates the full name */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char nameCh, capNameCh, lastNameCh;
    bool lastName = true;

    printf("Enter a first and last name: ");

    for (;;) {
        nameCh = getchar();
        if (nameCh == '\n') break;
        capNameCh = toupper(nameCh);

        if (lastName) {
            if (nameCh != capNameCh)
                lastName = false;
            else
                lastNameCh = nameCh;
        } else {
            if (capNameCh >= 'A' && capNameCh <= 'Z')
                printf("%c", nameCh);
        }
    }

    printf(", %c.\n", lastNameCh);

    return 0;
}
