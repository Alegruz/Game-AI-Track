/* Give the equivalent octal escape of following character escapes */

#include <stdio.h>

int main(void)
{
    char a = '\b',
            b = '\n',
            c = '\r',
            d = '\t';

    printf("\\b in octal is 0%o\n", a);
    printf("\\n in octal is 0%o\n", b);
    printf("\\r in octal is 0%o\n", c);
    printf("\\t in octal is 0%o\n", d);

    return 0;
}
