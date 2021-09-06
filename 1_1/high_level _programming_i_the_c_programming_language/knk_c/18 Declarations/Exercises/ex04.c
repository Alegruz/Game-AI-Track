int f(int i) {
    static int j = 0;
    return i * j++;
}

/* Value of f(10) if f has never been called before:            0  */
/* Value of f(10) if f has been called five times previously:   50 */