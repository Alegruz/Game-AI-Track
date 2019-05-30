// Write code to change the value of a pointer.
// Write code to change the value to which the pointer points.

int main() {
    int i = 1;
    int *ptr_i = nullptr;
    ptr_i = &i;
    *ptr_i = 2;

    return 0;
}