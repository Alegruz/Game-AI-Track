/* Find the error and show how to fix it */

//bool has_zero(int a[], int n) {
//    for (int i = 0; i < n; i++)
//        if (a[i] == 0)
//            return true;
//        else
//            return false;
//}

bool has_zero(int a[], int n) {
    for (int i = 0; i< n; i++)
        if (a[i] == 0)
            return true;
    return false;
}
