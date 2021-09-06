// Rewrite the programs from the previous exercises using a type alias for the type of the loop control variables.
#include <iostream>

using int_array = int[3];
using namespace std;
typedef int int_array[3];

int main() {
    int ia[2][3] = {0, 1, 2,
                    3, 4, 5};

    for (int_array *p = ia; p != ia + 2; ++p) {
        for (int *q = *p; q != *p + 3; ++q)
            cout << *q << ' ';
        cout << endl;
    }

    return 0;
}