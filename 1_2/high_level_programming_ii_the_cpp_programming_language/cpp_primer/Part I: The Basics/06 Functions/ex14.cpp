// Give an example of when a parameter should be a reference type.
// Give an example of when a parameter should not be a reference.

// parameter should be a reference type
int compare_int(const int &i, const int &j) {
    if (i < j)
        return -1;
    else if (i > j)
        return 1;
    return 0;
}

// parameter should not be a reference
int initialize_int(int i) {
    i = 0;
    return i;
}