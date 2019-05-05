#include <stdio.h>

#if defined(DEBUG)
#define PRINT_DEBUG(n) printf("Value of " #n ": %d\n", n)
#else
#define PRINT_DEBUG(n)
#endif // DEBUG