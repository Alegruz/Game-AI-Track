/* Write the functions rotate_left, rotate_right */

#include <stdio.h>

unsigned int rotate_left(unsigned int i, int n);
unsigned int rotate_right(unsigned int i, int n);

int main(void) {
    unsigned int i;
    int j;

    printf("Enter a hexaecimal number (up to eight digits): ");
    scanf("%x", &i);
    printf("How many times do you want to rotate the number: ");
    scanf("%d", &j);
    printf("Rotated left: %x, Rotated right: %x\n", rotate_left(i, j), rotate_right(i, j));

    return 0;
}

unsigned int rotate_left(unsigned int i, int n) {
    unsigned int remains = i >> sizeof(int) * (8 - n);
    return (i << sizeof(int) * n) | remains;
}

unsigned int rotate_right(unsigned int i, int n) {
    unsigned int remains = i << sizeof(int) * (8 - n);
    return (i >> sizeof(int) * n) | remains;
}
