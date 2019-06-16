// Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76) with appropriate using declarations.

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    cout << "Enter two integers that represents a range: ";
    int v1 = 0, v2 = 0;
    cin >> v1 >> v2;
    while (v1 <= v2) {
        cout << v1 << " and counting..." << endl;
        ++v1;
    }

    return 0;
}