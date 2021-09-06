/* Prints the English word for the number */

#include <stdio.h>

int main(void) {
    int first_digit, second_digit;

    printf("Enter a two-digit number: ");
    scanf("%1d%1d", &first_digit, &second_digit);

    printf("You entered the number ");

    if (first_digit > 1) {
        switch (first_digit) {
        case 2: printf("twenty"); break;
        case 3: printf("thirty"); break;
        case 4: printf("fourty"); break;
        case 5: printf("fifty"); break;
        case 6: printf("sixty"); break;
        case 7: printf("seventy"); break;
        case 8: printf("eighty"); break;
        case 9: printf("ninety"); break;
        }
        switch (second_digit) {
                case 1: printf("-one"); break;
                case 2: printf("-two"); break;
                case 3: printf("-three"); break;
                case 4: printf("-four"); break;
                case 5: printf("-five"); break;
                case 6: printf("-six"); break;
                case 7: printf("-seven"); break;
                case 8: printf("-eight"); break;
                case 9: printf("-nine"); break;
        }
    } else {
        switch (second_digit) {
                case 1: printf("eleven"); break;
                case 2: printf("twelve"); break;
                case 3: printf("thir"); break;
                case 4: printf("four"); break;
                case 5: printf("fif"); break;
                case 6: printf("six"); break;
                case 7: printf("seven"); break;
                case 8: printf("eigh"); break;
                case 9: printf("nine"); break;
                } if (second_digit > 2) printf("teen");
    }
    printf(".\n");

    return 0;
}
