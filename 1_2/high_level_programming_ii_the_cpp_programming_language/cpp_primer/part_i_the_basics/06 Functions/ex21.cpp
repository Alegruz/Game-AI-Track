// Write a function that takes an int and a pointer
// to an int and returns the larger of the int value
// or the value to which the pointer points.
// What type should you use for the pointer?
int f(const int i, const int *const pi) {
    return (i > *pi) ? i : *pi;
}