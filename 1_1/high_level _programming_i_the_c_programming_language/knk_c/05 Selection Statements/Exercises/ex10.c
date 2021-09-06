/* Shows the output of the following program fragment */

#include <stdio.h>

int main(void) {
    int i = 1;
    switch (i % 3) {
    case 0: printf("zero");
    case 1: printf("one");
    case 2: printf("two");
    } /* <onetwo> */

    return 0;
}
