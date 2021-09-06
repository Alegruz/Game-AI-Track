/* Write the function test_extension(file_name, extension) */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool test_extension(const char *_file_name, const char *_extension);

int main(void) {
    char file_name[] = "string.txt";
    char extension[] = "TXT";

    printf("result: %d\n", test_extension(file_name, extension));

    return 0;
}

bool test_extension(const char *_file_name, const char *_extension) {
    int extension_index = 0, char_count = 0;

    while (*_file_name) {
        if (extension_index > 0)
            char_count += (toupper(*_file_name) == toupper(*(_extension + extension_index++ - 1)));
        extension_index += (*_file_name == '.');
        _file_name++;
    }

    return (strlen(_extension) == char_count);
}
