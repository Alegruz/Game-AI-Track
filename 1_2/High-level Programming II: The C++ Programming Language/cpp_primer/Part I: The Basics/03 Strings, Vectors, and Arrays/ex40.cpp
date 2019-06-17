// Write a program to define two character arrays initialized from string literals.
// Now define a third character array to hold the concatenation of the two arrays.
// Use strcpy and strcat to copy the two arrays into the third.
#include <cstring>

int main() {
    char ch_arr1[] = "string";
    char ch_arr2[] = "literals";

    char result[] = "";
    strcpy(result, ch_arr1);
    strcat(result, ch_arr2);

    return 0;
}