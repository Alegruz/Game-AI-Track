// Rewrite each of the following old-style casts to use a named cast:
#include <string>

using namespace std;

int main() {
    int i;  double d;  const string *ps;  char *pc;  void *pv;
    pv = static_cast<void *>(const_cast<string *>(ps));
    // pv = const_cast<string *>(ps);
    i = static_cast<int>(*pc);
    pv = &d;
    pc = static_cast<char *>(pv);
    return 0;
}
