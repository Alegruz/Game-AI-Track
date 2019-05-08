/* char -> 1 byte
 * int -> 4 bytes
 * double -> 8 bytes
 * u -> ??
 */
union {
    double a;       /* 8 */
    struct {
        char b[4];  /* 4 */
        double c;   /* 4 + 8 */
        int d;      /* 4 + 8 + 4 */
    } e;            /* 16 */
    char f[4];      /* 4 */
} u;                /* 16 */
