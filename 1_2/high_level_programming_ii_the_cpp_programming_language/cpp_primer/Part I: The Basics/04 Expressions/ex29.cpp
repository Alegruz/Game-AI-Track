// Predict the output of the following code and explain your reasoning.
// Now run the program.
// Is the output what you expected? If not, figure out why.
#include <iostream>

using namespace std;

int main() {
    int x[10];   int *p = x;
    cout << sizeof(x)/sizeof(*x) << endl;   // 4 * 10 / 4 == 10
    cout << sizeof(p)/sizeof(*p) << endl;   // 8 / 4 == 2
    return 0;
}