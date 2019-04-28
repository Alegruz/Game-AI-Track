/* Rewrite the two nested for loop program fragment */

#include <stdio.h>

#define N 10

int main(void) {
    double ident[N][N];
    int counts = N;
    for (double *p = &ident[0][0]; p <= &ident[N - 1][N - 1]; ++p)
        if (counts == N) {
            *p = 1.0;
            counts = 0;
        } else if (counts >= 0 && counts < N) {
            *p = 0.0;
            counts++;
        }

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col)
            printf("%.2lf ", ident[row][col]);
        printf("\n");
    }
}
