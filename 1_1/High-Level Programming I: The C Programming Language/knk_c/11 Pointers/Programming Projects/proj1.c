/* US dollar amount to how to pay that amount using the smalles number of $20, $10, $5, and $1 bills */

#include <stdio.h>

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones);

int main(void) {
    int dollar, _20_bills, _10_bills, _5_bills, _1_bills;

    printf("Enter a dollar amount: ");
    scanf("%d", &dollar);

    pay_amount(dollar, &_20_bills, &_10_bills, &_5_bills, &_1_bills);

    printf("$20 bills: %d\n", _20_bills);
    printf("$10 bills: %d\n", _10_bills);
    printf(" $5 bills: %d\n", _5_bills);
    printf(" $1 bills: %d\n", _1_bills);

    return 0;
}

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones) {
    *twenties = dollars / 20;
    *tens = (dollars - *twenties * 20) / 10;
    *fives = (dollars - (*twenties * 20 + *tens * 10)) / 5;
    *ones = (dollars - (*twenties * 20 + *tens * 10 + *fives * 5));
}
