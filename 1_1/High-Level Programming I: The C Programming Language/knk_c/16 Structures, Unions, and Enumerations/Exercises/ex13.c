#define RECTANGLE 0
#define CIRCLE 1

struct point { int x, y; };

struct shape {
    int shape_kind;             /* RECTANGLE or CIRCLE */
    struct point center;        /* coordinates of center */
    union {
        struct {
            int height, width;
        } rectangle;
        struct {
            int radius;
        } circle;
    } u;
} s;

int main(void) {
    /* a */
    s.shape_kind = RECTANGLE;   /* added macro definitions */

    /* b */
    s.center.x = 10;

    /* c */
//    s.height = 25;
    s.u.rectangle.height = 25;

    /* d */
    s.u.rectangle.width = 8;

    /* e */
//    s.u.circle = 5;     /* struct circle is not int */

    /* f */
//    s.u.radius = 5;     /* radius is in struct circle */
    s.shape_kind = CIRCLE;
    s.u.circle.radius = 5;

    return 0;
}
