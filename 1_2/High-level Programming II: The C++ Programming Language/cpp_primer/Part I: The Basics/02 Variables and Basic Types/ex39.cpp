// Compile the following program to see what happens when you forget the semicolon after a class definition.
// Remember the message for future reference.

struct Foo { /* empty   */ } // Note: no semicolon
int main()
{
    return 0;
}

// ex39.cpp:4:29: error: expected ‘;’ after struct definition
//  struct Foo { /* empty   */ } // Note: no semicolon
//                              ^
//                              ;