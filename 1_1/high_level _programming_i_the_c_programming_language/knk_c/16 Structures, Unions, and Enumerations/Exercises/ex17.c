enum {FALSE, TRUE} b;
int i;

int main(void) {
    /* a */
    b = FALSE;
    /* b */
    b = i;  /* i must be 0 or 1 */
    /* c */
    b++;    /* b must be 0 */
    /* d */
    i = b;
    /* e */
    i = 2 * b + 1;

    return 0;
}
