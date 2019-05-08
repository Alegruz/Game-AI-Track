/* char -> 1 byte
 * int -> 4 bytes
 * double -> 8 bytes
 * s -> ??
 */
struct {
    double a;       /* 8 */
    union {
        char b[4];  /* 4 */
        double c;   /* 8 */
        int d;      /* 4 */
    } e;            /* 8 + 8 */
    char f[4];      /* 8 + 8 + 4 */
} s;                /* 20 */
