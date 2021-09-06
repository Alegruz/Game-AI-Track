/* Write the function store_zeros(a, n) */

//void store_zeros(int a[], int n) {
//    for (int i = 0; i < n; i++)
//        a[i] = 0;
//}

void store_zeros(int *a, int n) {
    for (int *p = a; p < a + n; p++)
        *p = 0;
}
