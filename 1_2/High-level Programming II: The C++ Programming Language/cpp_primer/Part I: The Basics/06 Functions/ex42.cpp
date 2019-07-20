// Give the second parameter of make_plural (§ 6.3.2, p. 224)a default argument of 's'.
// Test your program by printing singular and plural versions of the words success and failure.
#include <string>
#include <iostream>

using namespace std;

string make_plural(size_t ctr, const string &word,
                               const string &ending = "s");

int main() {
    string word1 = "success";
    string word2 = "failure";

    cout << make_plural(1, word1) << "'s plural: " << make_plural(word1.size(), word1, "es") << endl;
    cout << make_plural(1, word2) << "'s plural: " << make_plural(word2.size(), word2) << endl;

    return 0;
}

// return the plural version of word if ctr is greater than 1
string make_plural(size_t ctr, const string &word,
                               const string &ending) {
    return (ctr > 1) ? word + ending : word;
}