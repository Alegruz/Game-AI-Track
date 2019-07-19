// Write three additional declarations for the function in the previous exercise.
// One should use a type alias, one should use a trailing return,
// and the third should use decltype.
// Which form do you prefer and why?
#include <string>

// PREVIOUS EXERCISE
std::string (&func1(int param))[10];

// TYPE ALIAS
typedef std::string str_arr[10];
str_arr &func2(int param);

using str_arr_ref = std::string (&)[10];
str_arr_ref func3(int param);

// TRAILING RETURN
auto func4(int param) -> std::string (&)[10];

// DECLTYPE
std::string (&temp)[10];
decltype(temp) func5(int param);

// I prefer TYPE ALIAS and TRAILING RETURN
// The reason I prefer TYPE ALIAS
//      Easy to understand.
//      Easy to code when the type is used multiple times.
// The reason I prefer TRAILING RETURN
//      You might forget what was that type alias.
//      Trailing return indicates the exact return type.