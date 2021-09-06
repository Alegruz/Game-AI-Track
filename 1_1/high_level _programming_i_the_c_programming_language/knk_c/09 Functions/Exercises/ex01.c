/* Locate the two errors and show how to fix them */

#include <stdio.h>

// double triangle_area(double base, height)  height has no paramter-typr
// double product;   parameter product is not inside the parentheses
// {
//     product = base * height;
//     return product / 2;
// }

double triangle_area(double base, double height, double product) {
    product = base * height;
    return product / 2;
}