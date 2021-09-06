// What would happen if the while loop on page 148 that prints the elements from a vector used the prefix increment operator?
#include <vector>
#include <iostream>

using namespace std;

int main() {
    std::vector<int> v(10, 2);
    auto pbeg = v.begin();
    // print elements up to the first negative value
    while (pbeg != v.end() && *pbeg >= 0)
        cout << ++*pbeg << endl; // starting the first *pbeg, it prints the incremented version forever.
    return 0;
}