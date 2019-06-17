// What does the following program do?
#include <iostream>

using namespace std;

int main() {
    const char ca[] = {'h', 'e', 'l', 'l', 'o'};
    const char *cp = ca;
    while (*cp) {   // until the string ends with a null character
        cout << *cp << endl;    // print the character and a new line
        ++cp;                   // proceed to the next character
    }

    return 0;
}