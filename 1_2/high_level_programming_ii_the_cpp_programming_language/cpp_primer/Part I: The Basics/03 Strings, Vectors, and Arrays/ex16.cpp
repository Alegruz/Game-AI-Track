// Write a program to print the size and contents of the vectors from exercise 3.13.
// Check whether your answers to that exercise were correct.
// If not, restudy § 3.3.1 (p. 97) until you understand why you were wrong.
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class T>
void read_vector(vector<T> v) {
    cout << "Size: " << v.size() << endl;   // prints the size
    cout << "Members: ";
    for (auto elem : v)
        cout << elem << " ";    // prints the contents
    cout << endl;
}

int main() {
    vector<int> v1;
    vector<int> v2(10);
    vector<int> v3(10, 42);
    vector<int> v4{10};
    vector<int> v5{10, 42};
    vector<string> v6{10};
    vector<string> v7{10, "hi"};

    read_vector(v1);
    read_vector(v2);
    read_vector(v3);
    read_vector(v4);
    read_vector(v5);
    read_vector(v6);
    read_vector(v7);

    return 0;
}
