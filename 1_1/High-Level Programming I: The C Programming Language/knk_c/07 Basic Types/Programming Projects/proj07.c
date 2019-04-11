/* Calculates two fractions entered by the user */

#include <stdio.h>

int main(void) {
    int num1, denom1, num2, denom2, result_num, result_denom;
    char oprtr;

    printf("Enter two fractions separated by an operator: ");
    scanf("%d / %d %c %d / %d", &num1, &denom1, &oprtr, &num2, &denom2);

    result_denom = denom1 * denom2;

    switch (oprtr) {
    case '+':
        result_num = num1 * denom2 + num2 * denom1;
        break;
    case '-':
        result_num = num1 * denom2 - num2 * denom1;
        break;
    case '*':
        result_num = num1 * num2;
        break;
    case '/':
        result_num = num1 * denom2;
        result_denom = denom1 * num2;
        break;
    }

    printf("The result is %d/%d\n", result_num, result_denom);

    return 0;
}
