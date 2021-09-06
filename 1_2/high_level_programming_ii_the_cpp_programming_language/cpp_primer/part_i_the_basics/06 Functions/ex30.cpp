// Compile the version of str_subrange as presented on page 223
// to see what your compiler does with the indicated errors.
#include <string>
#include <iostream>

using namespace std;


bool str_subrange(const string &str1, const string &str2);

int main() {
    bool result = str_subrange("What", "hey");

    cout << "Result: " << ((result) ? "True" : "False") << endl;

    return 0;
}

// incorrect return values, this code will not compile
bool str_subrange(const string &str1, const string &str2)
{
    // same sizes: return normal equality test
    if (str1.size() == str2.size())
        return str1 == str2;   // ok: == returns bool
    // find the size of the smaller string; conditional operator, see § 4.7 (p. 151)
    auto size = (str1.size() < str2.size())
                ? str1.size() : str2.size();
    // look at each element up to the size of the smaller string
    for (decltype(size) i = 0; i != size; ++i) {
        if (str1[i] != str2[i])
            return; // error #1: no return value; compiler should detect this error
    }
    // error #2: control might flow off the end of the function without a return
    // the compiler might not detect this error
}

// ex30.cpp: In function ‘bool str_subrange(const string&, const string&)’:
// ex30.cpp:31:13: error: return-statement with no value, in function returning ‘bool’ [-fpermissive]
//              return; // error #1: no return value; compiler should detect this error
//              ^~~~~~
