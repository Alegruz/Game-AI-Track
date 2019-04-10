/* Defines the types to represent their respective bits */

#include <stdio.h>
typedef char Int8;
typedef short int Int16;
typedef int Int32;


int main(void)
{
    Int8 a = 127;
    Int8 b = -128;
    Int16 c = 32767;
    Int16 d = -32768;
    Int32 e = 2147483647;
    Int32 f = -2147483648;

    return 0;
}
