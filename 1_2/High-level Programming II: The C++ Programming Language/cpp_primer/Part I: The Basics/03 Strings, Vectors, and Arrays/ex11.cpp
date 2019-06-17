// Is the following range for legal? If so, what is the type of c?
#include <string>

using namespace std;

int main() {
    const string s = "Keep out!";
    for (auto &c : s) { /* ...  */ }    // range is legal. c is a reference to const char

    return 0;
}