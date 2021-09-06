// Rewrite the grade clustering program from § 3.3.3 (p. 104) using iterators instead of subscripts.
#include <vector>
#include <iostream>

using namespace std;

int main() {
    // count the number of grades by clusters of ten: 0--9, 10--19, . .. 90--99, 100
    vector<unsigned> scores(11, 0); // 11 buckets, all initially 0
    unsigned grade;
    while (cin >> grade)        // read the grades
        if (grade <= 100) {       // handle only valid grades
            auto iter = scores.begin() + (grade / 10);
            ++(*iter);  // increment the counter for the current cluster
        }

    return 0;
}
