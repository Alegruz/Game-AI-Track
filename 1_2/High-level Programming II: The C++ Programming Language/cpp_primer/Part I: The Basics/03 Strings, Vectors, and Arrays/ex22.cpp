// Revise the loop that printed the first paragraph in text to instead change the elements in text that correspond to the first paragraph to all uppercase.
// After you’ve updated text, print its contents.
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> text;
    std::string input_string;
    while (getline(std::cin, input_string))
        text.push_back(input_string);

    for (auto iter = text.begin();
         iter != text.end() && !iter->empty(); ++iter) {
        for (auto &c: *iter)
            c = toupper(c);
        std::cout << *iter << std::endl;
    }

    return 0;
}
