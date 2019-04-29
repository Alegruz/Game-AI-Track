/* Condense count_spaces function of Section 13.4 */

int count_spaces(const char *s) {
    int count = 0;
    while (*s) {
        count += (*s++ == ' ');
    }
    return count;
}
