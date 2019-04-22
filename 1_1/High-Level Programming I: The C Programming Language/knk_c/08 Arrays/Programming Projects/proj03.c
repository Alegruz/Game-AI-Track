/* Modify repdigit.c */

#include <stdbool.h>    /* C99 only */
#include <stdio.h>

int main(void) {
    bool digit_seen[10] = {false};
    long digit[255] = {0};
    long temp_digit;
    long n;
    int digit_index = 0;

    printf("Enter a number (enter 0 or below to stop): ");
    do {
        scanf("%ld", &n);
        if (n <= 0)
            break;
        digit[digit_index] = n;
        digit_index++;
    } while (n > 0);

    for (int i = 0; i < 255 && digit[i] > 0; ++i) {
        temp_digit = digit[i];
        while (temp_digit > 0) {
            n = temp_digit % 10;
            if (digit_seen[n] == true)
                break;
            digit_seen[n] = true;
            temp_digit /= 10;
        }
    }

    for (int i = 0; i < 255 && digit[i] > 0; ++i) {
        if (digit_seen[i] == true)
            printf("Repeated digit ");
        else
            printf("No repeated digit ");
        printf("in number %ld\n", digit[i]);
    }

    return 0;
}
