# Warning
Readers should be aware that they must add appropriate `#include` and `using` declarations to our examples before compiling them.

# Note
In addition to specifying the operations that the library types provide, the standard also imposes efficiency requirements on implementors.<br>
As a result, library types are efficient enough for general use.

# Note
The newline that causes `getline` to return is discarded; the newline is not stored in the `string`.

# Tip
You can avoid problems due to conversion between `unsigned` and `int` by not using `int`s in expressions that use `size()`.