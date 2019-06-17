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