// Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76) with appropriate using declarations.

#include <iostream>

using std::cout;
using std::endl;

int main()
{
    int count = 10;
    while (count >= 0) {
        cout << count << " and counting..," << endl;
        --count;
    }

    return 0;
}