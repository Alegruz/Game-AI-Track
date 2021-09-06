/* Calculates the remaining balance on a loan after three consecutive monthly payments */

#include <stdio.h>

int main(void) {
  float loan, interest_rate, monthly_payment;
  
  printf("Enter amount of loan: ");
  scanf("%f", &loan);
  printf("Enter interest rate: ");
  scanf("%f", &interest_rate);
  printf("Enter monthly payment: ");
  scanf("%f", &monthly_payment);
  
	loan = loan * (1 + (interest_rate / 12) / 100.f) - monthly_payment;
	printf("Balance remaining after first payment: $%.2f\n", loan);
	loan = loan * (1 + (interest_rate / 12) / 100.f) - monthly_payment;
	printf("Balance remaining after second payment: $%.2f\n", loan);
	loan = loan * (1 + (interest_rate / 12) / 100.f) - monthly_payment;
	printf("Balance remaining after third payment: $%.2f\n", loan);
  
  return 0;
}
