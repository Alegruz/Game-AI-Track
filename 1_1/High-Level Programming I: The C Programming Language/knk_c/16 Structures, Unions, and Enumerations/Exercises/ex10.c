#include <stdbool.h>

struct point { int x, y; };
struct rectangle { struct point upper_left, lower_right; };

int get_area(const struct rectangle r);
struct point get_center(const struct rectangle r);
struct rectangle move_rectangle(struct rectangle r, const int x, const int y);
bool is_in_rectangle(const struct point p, const struct rectangle r);

/* a */
int area(const struct rectangle r) {
    return (r.lower_right.x - r.upper_left.x) * (r.upper_left.y - r.lower_right.y);
}

/* b */
struct point get_center(const struct rectangle r) {
    return (struct point) {.x = (r.upper_left.x + r.lower_right.x) / 2,
                .y = (r.upper_left.y + r.lower_right.y) / 2};
}

/* c */
struct rectangle move_rectangle(struct rectangle r, const int x, const int y) {
    return (struct rectangle) {.upper_left = (struct point) {.x = r.upper_left.x + x, .y = r.upper_left.y + y},
                .lower_right = (struct point) {.x = r.lower_right.x + x, .y = r.lower_right.y + y}};
}

/* d */
bool is_in_rectangle(const struct point p, const struct rectangle r) {
    return (r.upper_left.x <= p.x && p.x <= r.lower_right.x &&
            r.lower_right.y <= p.y && p.y <= r.upper_left.y);
}
