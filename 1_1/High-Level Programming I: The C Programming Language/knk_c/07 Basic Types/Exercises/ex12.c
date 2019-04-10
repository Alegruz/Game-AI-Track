/* Figure out the type of the converted expression */

#include <stdio.h>

int main(void)
{
    int i = 1;
    float f = 2.5f;
    double d;
    
    d = i + f;
    /* Arithmetic conversion occurs, int + float becomes float */
    /* Then assignment conversion takes place. Float is assigned to double, making float converted to double */

    return 0;
}
