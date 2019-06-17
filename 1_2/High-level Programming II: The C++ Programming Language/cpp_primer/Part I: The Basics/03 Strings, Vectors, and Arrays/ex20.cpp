// Read a set of integers into a vector.
// Print the sum of each pair of adjacent elements.
// Change your program so that it prints the sum of the first and last elements, followed by the sum of the second and second-to-last, and so on.
#include <iostream>
#include <vector>

int main() {
    int i;
    std::vector<int> ivec;
    while (std::cin >> i)   // Read a set of integers
        ivec.push_back(i);  // into a vector
    
    // for (decltype(ivec.size()) i = 0;
    //     i < ivec.size() - 1; ++i)
    //     std::cout << "Sum of ivec[" << i << "] + ivec[" << i << " + 1]: "
    //                 << ivec[i] + ivec[i+1] << std::endl;    // Print the sum of each pair of adjacent elements
    for (decltype(ivec.size()) i = 0;
        i < ivec.size(); ++i)
        std::cout << ivec[i] << " " << ivec[ivec.size() - 1 - i] << std::endl;

    return 0;
}