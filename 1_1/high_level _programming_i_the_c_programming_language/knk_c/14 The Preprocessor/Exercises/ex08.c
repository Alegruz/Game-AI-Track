#include <stdio.h>

#define LINE_FILE "Line " STRINGIZE(__LINE__) " of file " __FILE__
#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x

int main(void) {
    const char *str = LINE_FILE;

    printf("%s\n", str);

    return 0;
}
