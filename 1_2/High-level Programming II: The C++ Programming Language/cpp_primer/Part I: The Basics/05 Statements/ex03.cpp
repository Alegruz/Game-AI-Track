// Use the comma operator (§ 4.10, p. 157) to rewrite the while loop from § 1.4.1 (p. 11)
// so that it no longer requires a block.
// Explain whether this rewrite improves or diminishes the readability of this code.

int main() {
    int val = 0, sum = 0;
    // keep executing the while as long as val is less than or equal to 10
    // while (val <= 10)  {
    //     sum += val;   // assigns sum + val to sum
    //     ++val;        // add 1 to val
    // }

    while (val <= 10)
        sum += val, ++val;  // might look cleaner than compound statements, but readability decreases.

    return 0;
}