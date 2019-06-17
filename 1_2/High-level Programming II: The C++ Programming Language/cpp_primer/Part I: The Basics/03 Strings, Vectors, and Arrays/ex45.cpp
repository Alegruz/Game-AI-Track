// Rewrite the programs again, this time using auto.
#include <iostream>

int main() {
    int ia[2][3] = {0, 1, 2,
                    3, 4, 5};

    for (auto p = ia; p != ia + 2; ++p) {
        for (auto q = *p; q != *p + 3; ++q)
            std::cout << *q << " ";
        std::cout << std::endl;
    }

    return 0;
}