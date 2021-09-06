/* List all variables and parameter names visible in the following scopes
 * (a) the f function                          (b) the g function
 * (c) the block in which a and d are declared (d) the main function               */

int b, c;

/* (a)
 * variables:       ex::b, c, f::b, d */
void f(void) {
    int b, d;
}

/* (b)
 * variables:       b, ex::c, g::c
 * paramter names:  a               */
void g(int a) {
    int c;
    /* (c)
     * variables: b, ex::c, g::a, g::c, a, d */
    {
        int a, d;
    }
}

/* (d)
 * variables: b, ex::c, main::c, d */
int main(void) {
    int c, d;
}
