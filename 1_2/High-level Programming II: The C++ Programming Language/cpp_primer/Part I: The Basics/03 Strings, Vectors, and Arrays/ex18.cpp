// Is the following program legal?
// If not, how might you fix it?
#include <vector>

using namespace std;

int main() {
    vector<int> ivec;
    // ivec[0] = 42;    illegal. subscripting an empty vector is illegal
    ivec.push_back(42);
    return 0;
}