// Write your own versions of each of the print functions presented in this section.
// Call each of these functions to print i and j defined as follows:
#include <iostream>

void print_marker(const int *cp);
void print_stl(const int *beg, const int *end);
void print_size(const int ia[], size_t size);
void print_arr_ref(int (&arr)[2]);

int main() {
    int i = 0, j[2] = {0, 1};

    print_marker(j);
    print_stl(j, &j[2]);
    print_size(j, 2);
    print_arr_ref(j);

    return 0;
}

void print_marker(const int *cp) {
    if (!cp)
        while (cp)
            std::cout << *cp;

    std::cout << std::endl;
}

void print_stl(const int *beg, const int *end) {
    while (beg != end)
        std::cout << *beg++;

    std::cout << std::endl;
}

void print_size(const int ia[], size_t size) {
    for (size_t i = 0; i < size; ++i)
        std::cout << ia[i];

    std::cout << std::endl;
}

void print_arr_ref(int (&arr)[2]) {
    for (auto elem : arr)
        std::cout << elem;

    std::cout << std::endl;
}
