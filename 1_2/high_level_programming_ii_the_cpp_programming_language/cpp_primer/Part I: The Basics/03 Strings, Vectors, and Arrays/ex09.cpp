// What does the following program do? Is it valid?
// If not, why not?
#include <string>
#include <iostream>

using namespace std;

int main() {
    string s;
    cout << s[0] << endl;   // Invalid. string is empty. indefined behavior expected.
                            // Expectation though: null character
    return 0;
}