/* Prints the value and the type of each expressions according to the declarations */

#include <stdio.h>

int main(void)
{
    char c = '\1';
    short s = 2;
    int i = -3;
    long m = 5;
    float f = 6.5f;
    double d = 7.5;

    printf("(a) c * i >> VALUE: %d, TYPE: int, SIZE: %d == %d\n", c * i, sizeof (c * i), sizeof (int));
    printf("(b) s + m >> VALUE: %ld, TYPE: long, SIZE: %d == %d\n", s + m, sizeof (s + m), sizeof (long));
    printf("(c) f / c >> VALUE: %.2f, TYPE: float, SIZE: %d == %d\n", f / c, sizeof (f / c), sizeof (float));
    printf("(d) d / s >> VALUE: %.2lf, TYPE: double, SIZE: %d == %d\n", d / s, sizeof (d / s), sizeof (double));
    printf("(e) f - d >> VALUE: %.2lf, TYPE: double, SIZE: %d == %d\n", f - d, sizeof (f - d), sizeof (double));
    printf("(f) (int) f >> VALUE: %d, TYPE: int, SIZE: %d == %d\n", (int) f, sizeof ((int) f), sizeof (int));


    return 0;
}
