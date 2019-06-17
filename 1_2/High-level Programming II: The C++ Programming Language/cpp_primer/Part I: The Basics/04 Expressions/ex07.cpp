// What does overflow mean? Show three expressions that will overflow.

int main() {
    long ln = 9223372036854775807;  //2^63 - 1. largest long.
    int in = ln;    // overflow

    in = 2147483647;    // 2^31 - 1. largest int
    short sn = in;    // overflow
    
    sn = 32767; //2^15 - 1. largest short
    char cn = sn;    // overflow

    return 0;
}