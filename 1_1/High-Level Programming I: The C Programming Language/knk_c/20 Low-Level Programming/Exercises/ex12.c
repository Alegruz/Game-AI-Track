#include <stdio.h>

unsigned short create_short(unsigned char high_byte, unsigned char low_byte);

int main(void) {
    unsigned char high = 0x12;
    unsigned char low = 0x34;

    printf("%hx\n", create_short(high, low));

    return 0;
}

unsigned short create_short(unsigned char high_byte, unsigned char low_byte) {
    return (high_byte << 8) + low_byte;
}

//unsigned short create_short(unsigned char high_byte, unsigned char low_byte) {
//    union {
//        unsigned short new_short;
//        struct {
//            unsigned char high;
//            unsigned char low;
//        } s;
//    } u;

//    u.s.low = low_byte;
//    u.s.high = high_byte;

//    return u.new_short;
//}
