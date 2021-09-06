// Write a program to compare two arrays for equality.
// Write a similar program to compare two vectors.
#include <vector>

int main() {
    int iarr1[10] = {};
    int iarr2[10] = {};

    for (int *p1 = iarr1, *p2 = iarr2;
        p1 != iarr1 + 10 && p2 != iarr2 + 10;
        ++p1, ++p2)
        if (*p1 > *p2)
            return 1;
        else if (*p1 < *p2)
            return -1;
    
    std::vector<int> ivec1(10, 0);
    std::vector<int> ivec2(10, 1);

    decltype(ivec1.size()) vec_size = (ivec1.size() < ivec2.size()) ? ivec1.size() : ivec2.size();
    for (decltype(ivec1.size()) i = 0; i < vec_size; ++i)
        if (ivec1[i] > ivec2[i])
            return 1;
        else if (ivec1[i] < ivec2[i])
            return -1;
    
    if (ivec1.size() > ivec2.size())
        return 1;
    else if (ivec1.size() < ivec2.size())
        return -1;

    return 0;
}