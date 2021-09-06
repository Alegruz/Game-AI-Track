/* Rewrite fact function without recursion */

int fact(int n) {
    int factorial = 1;
    for (int i = 1; i <= n; ++i)
        factorial *= i;
    return factorial;
}
