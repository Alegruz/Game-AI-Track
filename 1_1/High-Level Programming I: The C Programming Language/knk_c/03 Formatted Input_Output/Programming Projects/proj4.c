/* Prompts the user to enter a telephone number in the form (xxx) xxx-xxxx
   and then displays the number in the form xxx.xxx.xxxx */
   
#include <stdio.h>

int main(void) {
  int tel1, tel2, tel3;
  
  printf("Enter phone number [(xxx) xxx-xxxx]: ");
  scanf("(%d) %d-%d", &tel1, &tel2, &tel3);
  
  printf("You entered %.3d.%.3d.%.4d\n", tel1, tel2, tel3);
  
  return 0;
}
