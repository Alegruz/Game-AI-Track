// Rewrite the programs again, this time using auto.
#include <iostream>
#include <cstddef>
#include <iterator>

int main() {
    int ia[2][3] = {0, 1, 2,
                    3, 4, 5};

    // range for
    for (auto &row : ia) {
        for (auto &col : row)
            std::cout << col << " ";
        std::cout << std::endl;
    }
    
    // subscripts
    for (size_t row = 0; row < 2; ++row) {
        for (size_t col = 0; col < 3; ++col)
            std::cout << ia[row][col] << " ";
        std::cout << std::endl;
    }

    // pointers
    for (int *p = &ia[0][0]; p <= &ia[1][2]; ++p)
        std::cout << *p << " ";

    return 0;
}