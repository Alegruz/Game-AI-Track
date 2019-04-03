/* Dispaly a float variable x in according formats */

#include <stdio.h>

int main(void) {
  float x = 12345.6789f;

  // Exponential notation : left-justified in a field of size 8: one digit after the decimal point.
  printf("%8.1e\n", x);
  
  // Exponential notation : right-justified in a field of size 10 : six digits after the decimal point
  printf("%-10.6e\n", x);
  
  // Fixed decimal notation : left-justified in a field of size 8: three digits after the decimal point.
  printf("%8.3f\n", x);
  
  // Fixed decimal notation : right-justified in a field of size 6: no digits after the decimal point.
  printf("%6.f\n", x);
  
  return 0;
}
