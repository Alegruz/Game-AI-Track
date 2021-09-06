/* Evaluate the polynomial differently : Horner's Rule */

#include <stdio.h>

int main(void) {
  int x, polynomial;
  
  printf("Enter value of x: ");
  scanf("%d", &x);
  polynomial = (((((((3 * x) + 2) * x) - 5) * x - 1) * x) + 7) * x - 6;
  
  printf("Result of 3x^5 + 2x^4 - 5x^3 - x^2 + 7x - 6 is %d\n", polynomial);
  
  return 0;
}
