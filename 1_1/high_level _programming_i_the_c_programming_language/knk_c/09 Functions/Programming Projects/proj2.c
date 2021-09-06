/* Displays the tax due according to the taxable income using functions */

#include <stdio.h>

float compute_tax(float income);

int main(void) {
    float income, tax;

    printf("Enter an income: ");
    scanf("%f", &income);

    tax = compute_tax(income);

    printf("Your tax is %.2f.\n", tax);

    return 0;
}

float compute_tax(float income) {
    int tax;
    if (income > 7000.00f) tax = 230.00f + 0.06f * income;
    else if (income >= 5250.00f) tax = 142.50f + 0.05f * income;
    else if (income >= 3750.00f) tax = 82.50f + 0.04f * income;
    else if (income >= 2250.00f) tax = 37.50f + 0.03f * income;
    else if (income >= 750.00f) tax = 7.50f + 0.02f * income;
    else tax = 0.01f * income;
    return tax;
}