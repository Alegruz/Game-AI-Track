/* Declares several int and float variables-without initializing them-and then prints their values */

#include <stdio.h>

int main(void) {
  int rand_int1, rand_int2, rand_int3;
  float rand_float1, rand_float2, rand_float3;
  
  printf("Random Integers: %d\n\t\t%d\n\t\t%d\n", rand_int1, rand_int2, rand_int3);
  printf("Random Floating-Point Numbers: %f\n\t\t\t%f\n\t\t\t%f\n", rand_float1, rand_float2, rand_float3);
  
  return 0;
}
