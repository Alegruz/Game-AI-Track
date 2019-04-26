// You must declare a typical function before you use it in a program.
// The easiest way to do so is to incorporate into the program a header that declares
// all the library functions in a given category. A header can also define any
// associated type definitions and macros. A header is as much a part of the
// library as the functions themselves. Most often, a header is a text file just
// like the you write to make a program.
// You use the #include directive in a C source file to make a header part
// of the translation unit. For example, the header <stdio. h> declares functions
// that perform input and output. A program that prints a simple message
// with the function printf consists of the single C source file:
/* a simple test program */
#include <stdio.h>
int main(void)
    {   /* say hello */
    printf("Hello\n");
    return (0);
    }
// A translator converts each translation unit to an object module, a form
// suitable for use with a given computer architecture (or machine). A linker
// combines all the object modules that make up a program. It incorporates
// any object modules you use from the C library as well. The most popular
// form of translator is a compilw. It produces an executable file. Ideally at least,
// an executable file contains only those object modules from the library that
// contain functions actually used by the program. That way, the program
// suffers no size penalty as the C library grows more extensive. (Another
// form of translator is an interpreter. It may include the entire C library as part
// of the program that interprets your program.)