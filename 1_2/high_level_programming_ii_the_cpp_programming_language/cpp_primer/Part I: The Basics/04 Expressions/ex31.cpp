// The program in this section used the prefix increment and decrement operators.
// Explain why we used prefix and not postfix.
// What changes would have to be made to use the postfix versions?
// Rewrite the program using postfix operators.
#include <vector>
// #include <iterator>

using namespace std;

int main() {
    vector<int> ivec(10, 2);
    vector<int>::size_type cnt = ivec.size();
    // assign values from size... 1 to the elements in ivec
    // for(vector<int>::size_type ix = 0;
    //     ix != ivec.size(); ++ix, --cnt) // Prefix operators tend to perform less operations than postfix operators.
    for (vector<int>::size_type ix = 0;
            ix != ivec.size(); ix++, cnt--)
        ivec[ix] = cnt;
    // result is the same.
    return 0;
}