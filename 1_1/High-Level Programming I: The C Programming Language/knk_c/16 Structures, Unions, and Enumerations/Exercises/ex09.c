#include <stdbool.h>

struct color
{
    int red;
    int green;
    int blue;
};

struct color make_color(int red, int green, int blue);
int getRed(struct color c);
bool equal_color(struct color color1, struct color color2);
struct color brighter(struct color c);
struct color darker(struct color c);

/* a */
struct color make_color(int red, int green, int blue) {
    return (struct color) {.red = (red > 0 && red <= 255) * red + (red > 255) * 255,
                .green = (green > 0 && green <= 255) * green + (green > 255) * 255,
                .blue = (blue > 0 && blue <= 255) * blue + (blue > 255) * 255};
}

/* b */
int getRed(struct color c) {
    return c.red;
}

/* c */
bool equal_color(struct color color1, struct color color2) {
    return (color1.red == color2.red && color1.blue == color2.blue && color1.green == color2.green);
}

/* d */
struct color brighter(struct color c) {
    int red, blue, green;
    if (c.red == 0 && c.blue == 0 && c.green == 0) {
        red = 3;
        blue = 3;
        green = 3;
    } else {
        red = (0 < c.red && c.red < 3) * 3 + (c.red >= 3) * c.red;
        blue = (0 < c.blue && c.blue < 3) * 3 + (c.blue >= 3) * c.blue;
        green = (0 < c.green && c.green < 3) * 3 + (c.green >= 3) * c.green;

        red /= 0.7;
        blue /= 0.7;
        green /= 0.7;
    }

    return (struct color) {.red = red, .blue = blue, .green = green};
}

/* d */
struct color darker(struct color c) {
    int red, blue, green;
    if (c.red == 0 && c.blue == 0 && c.green == 0) {
        red = 3;
        blue = 3;
        green = 3;
    } else {
        red = (0 < c.red && c.red < 3) * 3 + (c.red >= 3) * c.red;
        blue = (0 < c.blue && c.blue < 3) * 3 + (c.blue >= 3) * c.blue;
        green = (0 < c.green && c.green < 3) * 3 + (c.green >= 3) * c.green;

        red *= 0.7;
        blue *= 0.7;
        green *= 0.7;
    }

    return (struct color) {.red = red, .blue = blue, .green = green};
}
