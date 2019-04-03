/* Tell whether the two if statements are equivalent */

#include <stdio.h>

int main(void) {
    int score = 100;

    /* 1 */
    if (score >= 90)
        printf("A");
    else if (score >= 80)
        printf("B");
    else if (score >= 70)
        printf("C");
    else if (score >= 60)
        printf("D");
    else
        printf("F");

    /* 2 */
    if (score < 60)
        printf("F");
    else if (score < 70)
        printf("D");
    else if (score < 80)
        printf("C");
    else if (score < 90)
        printf("B");
    else
        printf("A");

    return 0;
} /* They are both equivalent */
