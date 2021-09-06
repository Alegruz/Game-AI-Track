/* Write the function build_index_url(domain, index_url) */

#include <stdio.h>
#include <string.h>

void build_index_url(const char *domain, char *index_url);

int main(void) {
    char index_url[100];

    build_index_url("naver.com", index_url);

    printf("%s\n", index_url);

    return 0;
}

void build_index_url(const char *domain, char *index_url) {
    strcpy(index_url, "http://www.");
    strcat(index_url, domain);
    strcat(index_url, "/index.html");
}
