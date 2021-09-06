#include <stdio.h>  /* Lines brought in from stdio.h */

//#define N = 10                = considered as a replacement-list
#define N 10                    /* Blank Line */
//#define INC(x) x+1
#define INC(x) (x+1)            /* Blank Line */
//#define SUB (x,y) x-y         (x,y) considered as a replacement-list
#define SUB(x,y) x-y            /* Blank Line */
#define SQR(x) ((x)*(x))        /* Blank Line */
//#define CUBE(x) (SQR(x)*x)
#define CUBE(x) (SQR(x)*(x))    /* Blank Line */
#define M1(x,y) x##y            /* Blank Line */
#define M2(x,y) #x #y           /* Blank Line */

int main(void) {
    int a[N], i, j, k, m;

    i = 3; j = 2;       /* i and j needs to be initialized */
#ifdef N    /* Blank Line */
    i = j;
#else       /* Blank Line */
    j = i;  /* Blank Line */
#endif      /* Blank Line */
    i = 10 * INC(j);    /* i = 10 * (j+1); >> i = 10 * (2+1) == 30 */
    k = 1;              /* k needs to be initialized */
    i = SUB(j, k);      /* i = j-k; >> i = 2-1 == 1 */
    i = SQR(SQR(j));    /* i = ((((j)*(j)))*(((j)*(j)))); >> i = ((2*2)*(2*2)) == 16 */
    i = CUBE(j);        /* i = (((j)*(j))*j); >> i = ((2*2)*2) == 8 */
    int jk = 0;
    i = M1(j, k);       /* i = jk; >> i = 0 */
    puts(M2(i, j));     /* puts("i" "j") >> puts("ij") */

#undef SQR      /* Blank Line */
//    i = SQR(j); using undefined macro is impossible
#define SQR     /* Blank Line */
    i = SQR(j); /* Blank Line -> i = (j) >> i = 2 */

    return 0;
}
