/* Reads and prints the column sums and the row sums of a 5x5 array */

#include <stdio.h>

int main(void) {
    int array5x5[5][5] = {{0}};
    int array_element;
    int column_sum[5] = {0}, row_sum[5] = {0};

    for (int row = 0; row < 5; ++row) {
        printf("Enter column %d: ", row + 1);
        for (int column = 0; column < 5; ++column) {
            scanf("%d", &array_element);
            array5x5[row][column] = array_element;
        }
    }

    for (int row = 0; row < 5; ++row)
        for (int column = 0; column < 5; ++column) {
            row_sum[row] += array5x5[row][column];
            column_sum[column] += array5x5[row][column];
        }

    printf("\nRow totals: ");
    for (int row = 0; row < 5; ++row)
        printf("%3d", row_sum[row]);
    printf("\nColumn totals: ");
    for (int column = 0; column < 5; ++column)
        printf("%3d", column_sum[column]);
    printf("\n");

    return 0;
}
