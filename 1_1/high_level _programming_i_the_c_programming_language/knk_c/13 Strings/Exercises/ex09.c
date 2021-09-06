/* Shows the value of s1 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char s1[] = "string", s2[] = "disconnected";

    strcpy(s1, "computer");     // s1 = "computer"
    strcpy(s2, "science");      // s2 = "science"
    if (strcmp(s1, s2) < 0)     // 'c' < 's'
        strcat(s1, s2);         // s1 = "computerscience"
    else
        strcat(s2, s1);
    s1[strlen(s1) - 6] = '\0';  // s1[15 - 6] = s1[9] = '\0'
                                // s1 = "computers"
    return 0;
}
