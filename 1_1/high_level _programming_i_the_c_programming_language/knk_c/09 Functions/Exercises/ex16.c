/* Condense fact function */

int fact(int n) {
    return n <= 1 ? 1 : fact(n - 1);
}
