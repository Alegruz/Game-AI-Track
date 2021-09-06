// Write a function that takes an initializer_list<int>
// and produces the sum of the elements in the list.
#include <initializer_list>

int sum(std::initializer_list<int> const &il) {
    int sum = 0;
    for (const auto &elem : il)
        sum += elem;

    return sum;
}
