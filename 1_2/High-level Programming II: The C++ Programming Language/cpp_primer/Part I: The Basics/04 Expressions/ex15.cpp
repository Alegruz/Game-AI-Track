// The following assignment is illegal. Why? How would you correct it?
int main() {
    double dval; int ival; int *pi;

    // dval = ival = pi = 0; assigning int * to int. error.
    dval = ival = (long) (pi = 0);
    
    return 0;
}