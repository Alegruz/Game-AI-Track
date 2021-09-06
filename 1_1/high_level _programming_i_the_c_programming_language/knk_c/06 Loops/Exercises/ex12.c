/* Modify prime tester in Section 6.4 */

#include <stdio.h>

int main(void)
{
    int d, n = 10;

    for (d = 2; d * d < n; ++d) {
        if (n % 2 == 0)
            break;
    } printf("%d is prime number\n", d);

    return 0;
}
