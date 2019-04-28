/* Tell why the statement is illegal, and how could it be fixed */

int main(void) {
    int a[10] = {};
    int *high, *low, *middle;
    low = &a[1];
    high = &a[4];

//    middle = (low + high) / 2;
    // INVALID OPERANDS TO BINARY EXPRESSINO ('int *' and 'int *')
    middle = low + (high - low) / 2;

    return 0;
}
