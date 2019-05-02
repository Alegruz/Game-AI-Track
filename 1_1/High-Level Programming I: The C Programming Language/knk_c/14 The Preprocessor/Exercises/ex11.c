#include <stdio.h>

#define ERROR(message,index) fprintf(stderr, message, index);

int main(void) {
    int index = 0;
    ERROR("Range error: index = %d\n", index);

    return 0;
}
