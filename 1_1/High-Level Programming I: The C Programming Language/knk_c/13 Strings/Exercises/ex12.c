/* Write the function get_extension(file_name, extension) */

#include <stdio.h>
#include <string.h>

void get_extension(const char *file_name, char *extension);

int main(void) {
    char s[] = "string.txt", s_ext[20];
    char t[] = "program", t_ext[20];

    get_extension(s, s_ext);
    get_extension(t, t_ext);

    printf("s: %s, %s\nt: %s, %s\n", s, s_ext, t, t_ext);

    return 0;
}

void get_extension(const char *file_name, char *extension) {
    while (*file_name) {
        if (*file_name++ == '.') {
            strcpy(extension, file_name);
            return;
        }
    }
    *extension = 0;
}
