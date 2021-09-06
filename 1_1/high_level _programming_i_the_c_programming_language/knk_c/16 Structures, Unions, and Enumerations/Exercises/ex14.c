#include <math.h>

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

int get_area(const struct shape s);
struct shape move_shape(const struct shape s, int x, int y);
struct shape scale_shape(const struct shape s, double c);

int main(void) {

    return 0;
}

/* a */
int get_area(const struct shape s) {
    if (s.shape_kind == RECTANGLE)
        return s.u.rectangle.width * s.u.rectangle.height;
    else if (s.shape_kind == CIRCLE)
        return (s.u.circle.radius * s.u.circle.radius * M_PI);
}

/* b */
struct shape move_shape(const struct shape s, int x, int y) {
    return (struct shape) {.shape_kind = s.shape_kind, .center = (struct point) {s.center.x + x, s.center.y + y} , .u = s.u};
}

/* c */
struct shape scale_shape(const struct shape s, double c) {
    struct shape new_s = s;
    if (s.shape_kind == RECTANGLE) {
        new_s.u.rectangle.width *= c;
        new_s.u.rectangle.height *= c;
    } else {
        new_s.u.circle.radius *= c;
    }

    return new_s;
}
