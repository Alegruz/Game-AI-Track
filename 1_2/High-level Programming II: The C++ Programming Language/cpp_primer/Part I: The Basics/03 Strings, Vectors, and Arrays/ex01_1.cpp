// Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76)
// with appropriate using declarations.

#include <iostream>

using std::cout;
using std::endl;

int main()
{
    int sum = 0, val  = 1;
    // keep executing the while as long as val is less than or equal to 10
    while (val <= 10)  {
        sum += val;   // assigns sum + val to sum
        ++val;        // add 1 to val
    }
    cout << "Sum of 1 to 10 inclusive is "
              << sum << endl;
    return 0;
}