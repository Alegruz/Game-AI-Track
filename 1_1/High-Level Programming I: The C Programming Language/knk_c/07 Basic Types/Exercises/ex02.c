/* Evaluates the value of following integer and floating-point constants */

#include <stdio.h>

int main(void)
{
    int a, b, c, d;
    float e;
    a = 010E2;
    b = 32.1E+5;
//    c = 0790;     invalid digit '9' in octal constant
//    d = 100_000;  invalid character '_' in integer constant
    e = 3.978e-2;

    return 0;
}
