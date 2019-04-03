/* Displays the value of a polynomial */

#include <stdio.h>

int main(void) {
  int x, polynomial;
  
  printf("Enter value of x: ");
  scanf("%d", &x);
  polynomial = (3 * x * x * x * x * x) + (2 * x * x * x * x) - (5 * x * x * x) - (x * x) + (7 * x) - 6;
  
  printf("Result of 3x^5 + 2x^4 - 5x^3 - x^2 + 7x - 6 is %d\n", polynomial);
  
  return 0;
}
