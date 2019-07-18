// Write a function to determine whether a string contains any capital letters.
// Write a function to change a string to all lowercase.
// Do the parameters you used in these functions have the same type?
// If so, why? If not, why not?
#include <string>

bool has_capital(const std::string &s) {    // Used const reference to 1. make sure value of s doesn't change
                                            //                         2. take string literals as arguments
    for (size_t i = 0; i < s.size(); ++i)
        if ('a' <= s[i] && s[i] <= 'z')
            return true;
    
    return false;
}

std::string to_lower(const std::string &s) {      // Used const reference to take string literals as arguments
    std::string new_s(s.size(), ' ');
    for (size_t i = 0; i < s.size(); ++i) {
        if ('A' <= s[i] && s[i] <= 'Z')
            new_s[i] = s[i] - 'A' +'a';
    }

    return new_s;
}