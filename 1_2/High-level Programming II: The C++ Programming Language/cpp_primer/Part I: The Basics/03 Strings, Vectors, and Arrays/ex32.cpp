// Copy the array you defined in the previous exercise into another array.
// Rewrite your program to use vectors.
#include <cstddef>
#include <vector>

int main() {
    constexpr int iarr_size = 10;
    int iarr1[iarr_size];
    int iarr2[iarr_size];

    for (size_t i = 0; i < iarr_size; ++i) {
        iarr1[i] = static_cast<int> (i);
        iarr2[i] = iarr1[i];    // copy the array into another array
    }

    // rewrite to use vectors
    std::vector<int> ivec1;
    std::vector<int> ivec2;

    for (int i = 0; i < 10; ++i)
        ivec1.push_back(i);
    
    ivec2 = ivec1;

    return 0;
}