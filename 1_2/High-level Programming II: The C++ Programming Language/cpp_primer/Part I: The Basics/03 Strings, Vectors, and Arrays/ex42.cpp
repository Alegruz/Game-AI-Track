// Write a program to copy a vector of ints into an array of ints.
#include <vector>

int main() {
    std::vector<int> ivec(10, 2);
    int iarr[10] = {};

    for (decltype(ivec.size()) i = 0; i < ivec.size(); ++i)
        iarr[i] = ivec[i];

    return 0;
}