// Revise the program you wrote in the exercises in § 6.3.2 (p. 228)
// that used recursion to print the contents of a vector
// to conditionally print information about its execution.
// For example, you might print the size of the vector on each call.
// Compile and run the program with debugging turned on and again with it turned off.
#include <iostream>
#include <vector>

void print_vector(std::vector<int>::iterator begin, std::vector<int>::iterator end);

int main() {

    std::vector<int> iv(20, 3);

    print_vector(iv.begin(), iv.end());

    return 0;
}

void print_vector(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    #if !defined(NDEBUG)
    std::cerr << "Size of the vector: " << end - begin << std::endl;
    #endif // NDEBUG
    
    if (begin != end) {
        std::cout << *begin++;
        print_vector(begin, end);
    }

    return;
}
