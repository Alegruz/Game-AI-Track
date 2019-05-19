extern float a;

void f(register double b) {
    static int c;
    auto char d;
}

/* variable storage class   duration    scope   linkage  */
/* a        extern          static      file    external */
/* b        register        automatic   block   none     */
/* c        static          static      block   none     */
/* d        auto            automatic   block   none     */