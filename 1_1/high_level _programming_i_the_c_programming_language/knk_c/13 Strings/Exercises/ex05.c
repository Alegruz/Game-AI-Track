/* Write a function capitalize */

char *capitalize(char *s) {
    char *p = s;

    while (*p++ && 'a' <= *p && *p <= 'z')
        *p += ('A' - 'a');
    return s;
}
