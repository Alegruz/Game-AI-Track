/* Values of i, x, and j after the call */

#include <stdio.h>

int main(void) {
  int i, j;
  float x;
  
  printf("Enter the value of i, x, j which are int, float, int: ");
  scanf("%d%f%d", &i, &x, &j);  // Enters 10.3 5 6
  
  printf("Value of i : %d\n", i); // Prints 10
  printf("Value of x : %f\n", x); // Prints 0.300000
  printf("Value of j : %d\n", j); // Prints 5
  
  return 0;
}
