/* Modify proj11.c from Chapter 7 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverse_name(char *name);

int main(void)
{
    char name[20];

    printf("Enter a first and last name: ");

    int i = 0;
    for (; i < 20 && (name[i] = getchar()) != '\n'; ++i)
        ;
    name[i] = '\0';

    reverse_name(name);

    printf("%s\n", name);

    return 0;
}

void reverse_name(char *name) {
    char new_name[20];
    int first_name_index[2] = {}, last_name_index[2] = {};
    int *names[2] = {first_name_index, last_name_index};
    int first_or_last = 0;
//    char previous_char;
    for (int i = 0; i < strlen(name); ++i) {
        printf("%c is %d.\n", name[i], name[i]);
        if (name[i] == ' ') {
            if (i > 0 && name[i - 1] != ' ') {
                printf("end of %d, position %d\n", first_or_last, i);
                names[first_or_last][1] = i - 1;
                first_or_last++;
            }
        } else {
            if (i == 0 || (i > 0 && name[i - 1] == ' ')) {
                printf("start of %d, position %d\n", first_or_last, i);
                names[first_or_last][0] = i;
            } else if (i + 1 == strlen(name)) {
                printf("end of %d, position %d\n", first_or_last, i);
                names[first_or_last][1] = i;
                first_or_last++;
            }
        }
    }
    char *first_name = (name + names[0][0]);
    *(first_name + names[0][1] - names[0][0] + 1) = '\0';
    char *last_name = (name + names[1][0]);
    *(last_name + names[1][1] - names[1][0] + 1) = '\0';
    printf("%s\n%s\n", first_name, last_name);
    strcpy(new_name, last_name);
    strcat(new_name, ", ");
    strncat(new_name, first_name, 1);
    strcat(new_name, ".");
    strcpy(name, new_name);
}
