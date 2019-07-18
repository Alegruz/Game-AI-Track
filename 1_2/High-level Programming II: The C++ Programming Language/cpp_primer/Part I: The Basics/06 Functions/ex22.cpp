// Write a function to swap two int pointers.
void swap_pointer(int *&pi1, int *&pi2) {
    int *const temp = pi1;
    pi1 = pi2;
    pi2 = temp;
}