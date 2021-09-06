/* Computes the dimensional weight of a 12" x 10" x 8" box */

#include <stdio.h>

int main(void) {
  // Intialize the variables
  int height = 8, length = 12, width = 10;
  int volume = height * length * width;
  int dimensional_weight = (volume + 165) / 166;
  
  printf("Dimensions: %dx%dx%d\n", length, width, height);
  printf("Volume (cubic inches): %d\n", volume);
  printf("Dimensional weight (pounds): %d\n", dimensional_weight);
  
  return 0;
}
