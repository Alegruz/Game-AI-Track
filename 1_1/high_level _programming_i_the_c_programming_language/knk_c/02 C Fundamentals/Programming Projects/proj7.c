/* US dollar amount to how to pay that amount using the smalles number of $20, $10, $5, and $1 bills */

#include <stdio.h>

int main(void) {
  int dollar, _20_bills, _10_bills, _5_bills, _1_bills;
  
  printf("Enter a dollar amount: ");
  scanf("%d", &dollar);
  
  _20_bills = dollar / 20;
  _10_bills = (dollar - _20_bills * 20) / 10;
  _5_bills = (dollar - (_20_bills * 20 + _10_bills * 10)) / 5;
  _1_bills = (dollar - (_20_bills * 20 + _10_bills * 10 + _5_bills * 5));
  
  printf("$20 bills: %d\n", _20_bills);
  printf("$10 bills: %d\n", _10_bills);
  printf(" $5 bills: %d\n", _5_bills);
  printf(" $1 bills: %d\n", _1_bills);
  
  return 0;
}
