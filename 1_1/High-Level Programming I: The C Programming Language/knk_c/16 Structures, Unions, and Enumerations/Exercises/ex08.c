struct color
{
    int red;
    int green;
    int blue;
};

/* a */
//#define MAGENTA (struct color) {255, 0, 255}
#define MAGENTA (struct color) {.red = 255, .blue = 255};
