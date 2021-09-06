/* List all variables and parameter names visible in the following scopes
 * (a) the f function                   (b) the g function
 * (c) the block in which e is declared (d) the main function               */

int a;

/* (a)
 * variables:       a, c
 * parameter names: b */
void f(int b) {
    int c;
}

/* (b)
 * variables: a, d */
void g(void) {
    int d;
    /* (c)
     * variables: a, d, e */
    {
        int e;
    }
}

/* (d)
 * variables: a, f */
int main(void) {
    int f;
}
