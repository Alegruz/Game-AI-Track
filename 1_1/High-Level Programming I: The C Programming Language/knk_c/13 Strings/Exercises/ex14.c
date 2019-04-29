/* Show the output */

#include <stdio.h>

int main(void) {
    char s[] = "Hsjodi", *p;

    for (p = s; *p; p++)
        --*p;
    puts(s);    // "Grinch"
    return 0;
}
