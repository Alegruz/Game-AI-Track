/* Write the function remove_filename(url) */

#include <stdio.h>
#include <string.h>

void remove_filename(char *url);

int main(void) {
    char url[] = "http://www.knking.com/index.html";

    remove_filename(url);

    puts(url);

    return 0;
}

void remove_filename(char *url) {
    char *p = url;
    for(p = url + strlen(url); *p != '/'; --p)
        ;
    *p = '\0';
}
