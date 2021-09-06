// Write a declaration for a function
// that takes two int parameters and returns an int, 
// and declare a vector whose elements have this function pointer type.
#include<vector>

int f(int, int);
typedef decltype(f) *pf1;
using pf2 = decltype(f) *;

int main() {
    std::vector<decltype(f) *> fv1;
    std::vector<pf1> fv2;
    std::vector<pf2> fv3;
    std::vector<int (*)(int, int)> fv4;

    return 0;
}