#include <stdio.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int REG;

union DWORD {
    struct {
        REG eax, ebx, ecx, edx;
    } reg;
    struct {
        WORD ax, ea, bx, eb, cx, ec, dx, ed;
    }  word;
    struct {
        BYTE al, ah, eal, eah, bl, bh, ebl, ebh,
        cl, ch, ecl, ech, dl, dh, edl, edh;
    } byte;
} regs;

