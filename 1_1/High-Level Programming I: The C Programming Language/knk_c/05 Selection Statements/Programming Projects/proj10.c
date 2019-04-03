/* Converts a numerical grade into a letter grade */

#include <stdio.h>

int main(void)
{
    int grade;

    printf("Enter numerical grade: ");
    scanf("%d", &grade);

    printf("Letter grade: ");
    switch (grade / 10) {
    case 10: case 9: printf("A"); break;
    case 8: printf("B"); break;
    case 7: printf("C"); break;
    case 6: printf("D"); break;
    default: printf("F"); break;
    } printf("\n");

    return 0;
}
