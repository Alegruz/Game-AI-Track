/* Give the equivalent hexadecimal escape of following character escapes */

#include <stdio.h>

int main(void)
{
    char a = '\b',
            b = '\n',
            c = '\r',
            d = '\t';

    printf("\\b in hexadecimal is 0x%x\n", a);
    printf("\\n in hexadecimal is 0x%x\n", b);
    printf("\\r in hexadecimal is 0x%x\n", c);
    printf("\\t in hexadecimal is 0x%x\n", d);

    return 0;
}
