/* a */
// char (*x1[10])(int);
typedef char A(int);
typedef A *A_ptr;
typedef A_ptr A_ptr_array[10];
A_ptr_array x1;

/* b */
// int (*x2(int))[5];
typedef int B_array[5];
typedef B_array *B_array_ptr;
typedef B_array_ptr B(int);
B x2;

/* c */
// float *(*x3(void))(int);
typedef float *C(int);
typedef C *C_ptr;
typedef C_ptr C_ptr_func(void);
C_ptr_func x3;

/* d */
// void (*x4(int, void (*y)(int)))(int);
typedef void D(int);
typedef D *D_ptr;
typedef void (*D_arg_func)(int);
typedef D_ptr D_func(int, D_arg_func);
D_func x4;