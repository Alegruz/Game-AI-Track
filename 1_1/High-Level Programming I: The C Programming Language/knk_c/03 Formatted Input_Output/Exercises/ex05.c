/* What will be the values of i, x, and j after the call? */

#include <stdio.h>

int main(void) {
  int i;
  float x, y;
  
  printf("Enter three consecutive values. Float, Integer then Float: ");
  scanf("%f%d%f", &x, &i, &y);  // Input is 12.3 45.6 789
  
  printf("Value of x : %f\n", x); // Output is 12.300000
  printf("Value of i : %d\n", i); // Output is 45
  printf("Value of y : %f\n", y); // Output is 0.600000
  
  return 0;
}
