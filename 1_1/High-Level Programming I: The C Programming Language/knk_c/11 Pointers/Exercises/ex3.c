/* Find and correct the errors */

void avg_sum(double a[], int n, double *avg, double *sum) {
//    sum = 0.0;
    *sum = 0.0;
    for (int i = 0; i < n; ++i)
//        sum += a[i];
        *sum += a[i];
//    avg = sum / n;
    *avg = *sum / n;
}
