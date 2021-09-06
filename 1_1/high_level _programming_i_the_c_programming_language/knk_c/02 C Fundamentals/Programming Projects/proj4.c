/* Dollars-and-cent amount to amount with 5% tax added */

#include <stdio.h>

#define TAX 0.05f

int main(void) {
  float amount;

  printf("Enter an amount: ");
  scanf("%f", &amount);
  
  printf("With tax added: $%.2f\n", amount * (1 + TAX));
  
  return 0;
}
