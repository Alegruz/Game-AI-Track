// Redo the last exercise from § 3.3.3 (p. 105) using iterators.
#include <iostream>
#include <vector>

int main() {
    int i;
    std::vector<int> ivec;
    while (std::cin >> i)   // Read a set of integers
        ivec.push_back(i);  // into a vector

    for (auto iter = ivec.cbegin(); iter != ivec.cend() - 1; ++iter)
        std::cout << *iter + *(iter + 1) << std::endl;

    for (auto iter = ivec.cbegin(); iter != ivec.cend(); ++iter)
        std::cout << *iter << " " << *(ivec.begin() + (ivec.cend() - 1 - iter)) << std::endl;

    return 0;
}
