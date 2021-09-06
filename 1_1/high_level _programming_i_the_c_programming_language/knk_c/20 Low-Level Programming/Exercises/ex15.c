#include <stdio.h>

/* a */
struct {
    int flag: 1;
} s1;

/* b */
struct {
    unsigned int flag: 1;
} s2;

int main(void) {
    s1.flag = 1;
    printf("%d\n", s1.flag); /* -1 */
    /* a: assigning int variable causes implementation behavior. */
    /* here, flag is treated as a sign bit. */

    s2.flag = 1;
    printf("%d\n", s2.flag); /* 1 */

    return 0;
}
