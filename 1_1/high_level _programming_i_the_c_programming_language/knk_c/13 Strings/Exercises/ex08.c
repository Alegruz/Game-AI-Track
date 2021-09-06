/* Prints the value of the string str */

#include <stdio.h>
#include <string.h>

int main(void) {
    char str[] = "string";
    strcpy(str, "tire-bouchon");    // str = "tire-bouchon"
    strcpy(&str[4], "d-or-wi");    // str2 = "tired-or-wi"
    strcat(str, "red?");           // str3 = "tired-or-wired?"

    return 0;
}
