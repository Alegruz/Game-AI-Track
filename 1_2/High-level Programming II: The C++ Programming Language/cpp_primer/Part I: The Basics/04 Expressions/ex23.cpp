// The following expression fails to compile due to operator precedence.
// Using Table 4.12 (p. 166), explain why it fails.\
// How would you fix it?
#include <string>

using namespace std;

int main() {
    string s = "word";
    string pl = s + (s[s.size() - 1] == 's' ? "" : "s"); // s + s[s.size() - 1] == 's' is evaluated first.
                                                        // however, s is a string and s[s.size() - 1] is a character
                                                        // thus s + (expr) is correct version.
    return 0;
}