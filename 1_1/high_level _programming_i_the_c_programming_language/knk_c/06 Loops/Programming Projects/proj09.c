/* Calculates the remaining balance on a loan after three consecutive monthly payments */

#include <stdio.h>

int main(void) {
    float loan, interest_rate, monthly_payment;
    int i, num_payment;

    printf("Enter amount of loan: ");
    scanf("%f", &loan);
    printf("Enter interest rate: ");
    scanf("%f", &interest_rate);
    printf("Enter monthly payment: ");
    scanf("%f", &monthly_payment);

    printf("Enter the number of payments: ");
    scanf("%d", &num_payment);

    for (i = 1; i <= num_payment; ++i) {
        loan = loan * (1 + (interest_rate / 12) / 100.f) - monthly_payment;
        printf("Balance remaining after %d", i);
        if ((i <= 20) && (i > 10)) {
            printf("th");
        } else {
            switch (i % 10) {
            case 1: printf("st"); break;
            case 2: printf("nd"); break;
            case 3: printf("rd"); break;
            default: printf("th"); break;
            }
        }
        printf(" payment: $%.2f\n", loan);
    }

  return 0;
}
