// Given two vectors of ints,
// write a program to determine whether one vector is a prefix of the other.
// For vectors of unequal length,
// compare the number of elements of the smaller vector.
// For example,
// given the vectors containing 0, 1, 1, and 2 and 0, 1, 1, 2, 3, 5, 8,
// respectively your program should return true.
#include <vector>
#include <iostream>

int main() {
    std::vector<int> ivec1, ivec2;
    
    int vector_member;
    while (std::cin >> vector_member)
        ivec1.push_back(vector_member);
    
    while (std::cin >> vector_member)
        ivec2.push_back(vector_member);
    
    decltype(ivec1.size()) size = (ivec1.size() < ivec2.size()) ? ivec1.size() : ivec2.size();

    int prefix_count = 0;
    for (decltype(size) i = 0; i < size; ++i) {
        if (ivec1[i] == ivec2[i])
            ++prefix_count;
        else
            break;
    }

    if (prefix_count == 0)
        return false;
    else
        return true;
}