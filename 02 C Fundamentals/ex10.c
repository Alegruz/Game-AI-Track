/* Computes the dimensional weight of a 12" x 10" x 8" box */

#include <stdio.h>

int main(void) {  // essential space (int-main)
  // Intialize the variables
  int height = 8, length = 12, width = 10;  // essential space (int-height)
  int volume = height * length * width; // // essential space (int-volume)
  int dimensional_weight = (volume + 165) / 166;  // essential space (int-dimensional_weight)
  
  printf("Dimensions: %dx%dx%d\n", length, width, height);
  printf("Volume (cubic inches): %d\n", volume);
  printf("Dimensional weight (pounds): %d\n", dimensional_weight);
  
  return 0; // essential space (return-0)
}
