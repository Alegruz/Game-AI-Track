/* Modify proj11.cfrom Chapter 5 */

#include <stdio.h>

int main(void) {
    const char *number_to_char[] = {"one", "two", "three", "four",
                                   "five", "six", "seven", "eight", "nine",
                                   "ten", "eleven", "twelve", "thirteen", "fourteen",
                                   "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    const char *tens_to_char[] = {"twenty", "thirty", "fourty", "fifty", "sixty",
                                  "seventy", "eighty", "ninety"};
    int first_digit, second_digit;

    printf("Enter a two-digit number: ");
    scanf("%1d%1d", &first_digit, &second_digit);

    printf("You entered the number ");

    if (0 <= first_digit && first_digit <= 1) {
        printf("%s", number_to_char[first_digit * 10 + second_digit - 1]);
    } else {
        printf("%s %s", tens_to_char[first_digit - 2], number_to_char[second_digit - 1]);
    }
    printf(".\n");

    return 0;
}
