// Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76) with appropriate using declarations.

#include <iostream>

using std::cout;
using std::endl;

int main() {
    int sum = 0, count = 50;
    while (count <= 100) {
        sum += count;
        ++count;
    }
    cout << "The sum of the numbers from 50 to 100 is "
                << sum << endl;

    return 0;
}