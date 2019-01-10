/* Enter the numbers from 1 to 16(in any order)
   and then displays the numbers in a 4 by 4 arrangement,
   followed by the sums of the rows, columns, and diagonals */
   
#include <stdio.h>

int main(void) {
  int n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15;
  
  printf("Enter the numbers from 1 to 16 in any order:\n");
  scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", 
  &n0, &n1, &n2, &n3, &n4, &n5, &n6, &n7, &n8, &n9, &n10, &n11, &n12, &n13, &n14, &n15);
  
  printf("%2d%3d%3d%3d\n", n0, n1, n2, n3);
  printf("%2d%3d%3d%3d\n", n4, n5, n6, n7);
  printf("%2d%3d%3d%3d\n", n8, n9, n10, n11);
  printf("%2d%3d%3d%3d\n", n12, n13, n14, n15);
  
  printf("Row sums: %d %d %d %d\n", 
  n0 + n1 + n2 + n3, n4 + n5 + n6 + n7, n8 + n9 + n10 + n11, n12 + n13 + n14 + n15);
  printf("Column sums: %d %d %d %d\n", 
  n0 + n4 + n8 + n12, n1 + n5 + n9 + n13, n2 + n6 + n10 + n14, n3 + n7 + n11 + n15);
  printf("Diagonal sums: %d %d\n", n0 + n5 + n10 + n15, n3 + n6 + n9 + n12);
  
  return 0;
}
