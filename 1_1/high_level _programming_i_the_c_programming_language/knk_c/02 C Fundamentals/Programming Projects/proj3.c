/* Computes the volume of a sphere from input provided by user */

#include <stdio.h>

#define PI 3.14159f

int main(void) {
  int radius;
  float sphere_volume;
  
  printf("Enter a radius of a sphere: ");
  scanf("%d", &radius);
  sphere_volume = (4.0f / 3.0f) * (PI * radius * radius * radius);
  
  printf("The volume of the sphere is %.2f\n", sphere_volume);
  
  return 0;
}
