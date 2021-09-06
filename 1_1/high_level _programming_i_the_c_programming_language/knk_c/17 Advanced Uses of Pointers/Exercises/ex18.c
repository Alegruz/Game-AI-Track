/* Modify compare_parts function */

struct part {
    int number;
    char *name;
    int on_hand;
};

int compare_parts(const void *p, const void *q) {
    return ((struct part *) q)->number - ((struct part *) p)->number;
}
