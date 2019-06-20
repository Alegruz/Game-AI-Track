// The last example in this section that jumped back to begin
// could be better written using a loop.
// Rewrite the code to eliminate the goto.

int get_size();

int main() {
    // backward jump over an initialized variable definition is okay
    begin:
        int sz = get_size();
        if (sz <= 0)
            goto begin;
    
    // 1
    int sz1 = get_size();
    while (sz1 <= 0)
        sz1 = get_size();
    
    // 2
    for (int sz2 = get_size(); sz2 <= 0; sz = get_size())
        ;

    return 0;
}