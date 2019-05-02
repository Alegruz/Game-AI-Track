#include <stdio.h>
#include <string.h>

//#define ENGLISH 1
//#define FRENCH 1
#define SPANISH 1

int main(void) {
#ifdef ENGLISH
    printf("Insert Disk 1\n");
#elif defined(FRENCH)
    printf("Inserez Le Disque 1\n");
#elif defined(SPANISH)
    printf("Inserte El Disco 1\n");
#endif
}
