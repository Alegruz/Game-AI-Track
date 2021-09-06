// Rewrite the program in the first exercise, first using a while and again using a traditional for loop.
// Which of the three approaches do you prefer and why?
#include <iostream>
#include <string>

int main() {
    std::string s;
    std::cin >> s;
    // for (auto &c : s)
    //     c = 'X';

    // decltype(s.size()) i = 0;
    // while (i != s.size()) {
    //     s[i] = 'X';
    //     ++i;
    // }

    for (decltype(s.size()) i = 0;
        i < s.size(); ++i)
        s[i] = 'X';

    std::cout << s << std::endl;

    return 0;
}

// I prefer the auto. it is neat, readable, easy to fix.
