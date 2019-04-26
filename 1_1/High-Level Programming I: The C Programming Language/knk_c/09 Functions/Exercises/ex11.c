/* Write a function compute_GPA(grades, n) */

#include <stdio.h>
#include <ctype.h>

float compute_GPA(char grades[], int n);

int main(void) {
    char grades[5];
    char ch;
    int i = 0;

    printf("GPA Calculator\nEnter 5 grades (A, B, C, D, F): ");
    for (;;) {
        ch = getchar();
        if (ch == '\n' && i >= 5)
            break;
        if (('A' <= toupper(ch) && toupper(ch) <= 'D') || toupper(ch) == 'F') {
            grades[i] = ch;
            i++;
        }
    }

    printf("Your GPA is %.2f.\n", compute_GPA(grades, 5));

    return 0;
}

float compute_GPA(char grades[], int n) {
    float GPA = 0.0f;

    for (int i = 0; i < n; ++i){
        switch (grades[i]) {
        case 'A':
            GPA += 4.0f; break;
        case 'B':
            GPA += 3.0f; break;
        case 'C':
            GPA += 2.0f; break;
        case 'D':
            GPA += 1.0f; break;
        }
    }

    return GPA / n;
}
