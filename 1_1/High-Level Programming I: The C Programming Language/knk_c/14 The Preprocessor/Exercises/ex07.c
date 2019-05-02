#define GENERIC_MAX(type)               \
    type type##_max(type x, type y) {   \
        return x > y ? x : y;           \
    }

/* (a) */
GENERIC_MAX(long);
/*  long long_max(long x, long y) {
 *      return x > y ? x : y;
 *  }
 */

/* b */
// GENERIC_MAX(unsigned long);
/*  unsigned long unsigned long_max(unsigned long x, unsigned long y) { -> unsigned long_max is the wrong part
 *      return x > y ? x : y;
 *  }
 */

/* c */
GENERIC_MAX(long unsigned);
