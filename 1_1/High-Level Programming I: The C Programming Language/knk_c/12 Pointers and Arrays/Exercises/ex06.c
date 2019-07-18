/* Rewrite the function sum_array to use pointer arithmetics */

//int sum_array(const int a[], int n) {
//    int i, sum;

//    sum = 0;
//    for (i = 0; i < n; i++)
//        sum += a[i];
//    return sum;
//}

int sum_array(const int *a, int n) {
    int sum = 0;

    for (int const *p = a; p < a + n; ++p)
        sum += *p;

    return sum;
}
