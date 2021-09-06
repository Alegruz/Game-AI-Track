/* Identify the storage class, type qualifiers, type specifiers, declarators, and initializers */

#define MAX_FILES 10

/* a */
static char **lookup(int level);
/* static sc, char ts, **lookup(int level) d */

/* b */
volatile unsigned long io_flags;
/* volatile tq, unsigned long ts, io_flags d */

/* c */
extern char *file_name[MAX_FILES], path[];
/* extern tq, char ts, *file_name[MAX_FILES] & path[] d */

/* d */
static const char token_buf[] = "";
/* static sc, const tq, char ts, token_buf[] d, "" i */