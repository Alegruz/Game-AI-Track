/* Computes the volume of a sphere with a 10-meter radius */

#include <stdio.h>

#define PI 3.14159f

int main(void) {
  int radius = 10;
  float sphere_volume_f = (4.0f / 3.0f) * (PI * radius * radius * radius);  // Produces proper result
  float sphere_volume = (4 / 3) * (PI * radius * radius * radius);  // Produces wrong result due to fraction made with integers
  
  printf("Radius of the sphere is %d\n", radius);
  printf("The volume of the sphere is %.2f\n", sphere_volume_f);
  printf("Another result would be %.2f\n", sphere_volume);
  
  return 0;
}
