## Advice: Managing Compound Expressions
When you write compound expressions, two rules of thumb can be helpful:
1. When in doubt, parenthesize expressions to force the grouping that the logic of your program requires.
2. If you change the value of an operand, don’t use that operand elsewhere in the same expresion.<br>
An important exception to the second rule occurs when the subexpression that changes the operand is itself the operand of another subexpression.

For example, in `*++iter`, the increment changes the value of `iter`.<br>
The (now changed) value of `iter` is the operand to the dereference operator.<br>
In this (and similar) expressions, order of evaluation isn’t an issue.<br>
The increment (i.e., the subexpression that changes the operand) must be evaluated before the dereference can be evaluated.<br>
Such usage poses no problems and is quite common.

## Caution: Overflow and Other Arithmetic Exceptions
Some arithmetic expressions yield undefined results.<br>
Some of these undefined expressions are due to the nature of mathematics—for example, division by zero.<br>
Others are undefined due to the nature of computers—for example, due to overflow.<br>
Overflow happens when a value is computed that is outside the range of values that the type can represent.<br>
Consider a machine on which `short`s are 16 bits.<br>
In that case, the maximum `short` is `32767`. On such a machine, the following compound assignment overflows:
```
short short_value = 32767; // max value if shorts are 16 bits
short_value += 1; // this calculation overflows
cout << "short_value: " << short_value << endl;
```
The assignment to `short_value` is undefined.<br>
Representing a `signed` value of `32768` requires 17 bits, but only 16 are available.<br>
On many systems, there is no compile-time or run-time warning when an overflow occurs.<br>
As with any undefined behavior, what happens is unpredictable.<br>
On our system the program completes and writes
<br>
`short_value: -32768`
<br>
The value “wrapped around”: The sign bit, which had been `0`, was set to `1`, resulting in a negative value.<br>
On another system, the result might be different, or the program might behave differently, including crashing entirely.

## Warning
It is usually a bad idea to use the boolean literals `true` and `false` as operands in a comparison.<br>
These literals should be used only to compare to an object of type `bool`.

## Note
Because assignment has lower precedence than the relational operators, parentheses are usually needed around assignments in conditions.

## Advice: Use Postfix Operators only When Necessary
Readers from a C background might be surprised that we use the prefix increment in the programs we’ve written.<br>
The reason is simple: The prefix version avoids unnecessary work.<br>
It increments the value and returns the incremented version.<br>
The postfix operator must store the original value so that it can return the unincremented value as its result.<br>
If we don’t need the unincremented value, there’s no need for the extra work done by the postfix operator.<br>
For `int`s and pointers, the compiler can optimize away this extra work.<br>
For more complicated iterator types, this extra work potentially might be more costly.<br>
By habitually using the prefix versions, we do not have to worry about whether the performance difference matters.<br>
Moreover—and perhaps more importantly—we can express the intent of our programs more directly.

## Advice: Brevity Can Be a Virtue
Expressions such as `*pbeg++` can be bewildering—at first.<br>
However, it is a useful and widely used idiom.<br>
Once the notation is familiar, writing `cout << *iter++ << endl;` is easier and less error-prone than the more verbose equivalent
```
cout << *iter << endl;
++iter;
```
It is worthwhile to study examples of such code until their meanings are immediately clear.<br>
Most C++ programs use succinct expressions rather than more verbose equivalents.<br>
Therefore, C++ programmers must be comfortable with such usages.<br>
Moreover, once these expressions are familiar, you will find them less error-prone.