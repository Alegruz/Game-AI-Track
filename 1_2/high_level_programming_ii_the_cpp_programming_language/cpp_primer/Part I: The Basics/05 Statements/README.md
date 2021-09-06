## Best Practices
Null statements should be commented.<br>
That way anyone reading the code can see that the statement was omitted intentionally.

## Warning
Extraneous null statements are not always harmless.

## Note
A block is not terminated by a semicolon.

## Best Practices
Many editors and development environments have tools to automatically indent source code to match its structure.<br>
It is a good idea to use such tools if they are available.

## Best Practices
Omitting a `break` at the end of a case happens rarely.<br>
If you do omit a `break`, include a comment explaining the logic.

## Best Practices
Although it is not necessary to include a `break` after the last label of a `switch`, the safest course is to provide one.<br>
That way, if an additional case is added later, the `break` is already in place.

## Best Practices
It can be useful to define a `default` label even if there is no work for the `default` case.<br>
Defining an empty `default` section indicates to subsequent readers that the case was considered.

## Note
Variables defined in a `while` condition or `while` body are created and destroyed on each iteration.

## Note
It is worth remembering that the visibility of any object defined within the `for` header is limited to the body of the `for` loop.<br>
Thus, in this example, index is inaccessible after the `for` completes.

## Note
A `do` `while` ends with a semicolon after the parenthesized condition.

## Best Practices
Programs should not use `goto`s.<br>
`goto`s make programs hard to understand and hard to modify.

## Caution: Writing Exception Safe Code is Hard
It is important to realize that exceptions interrupt the normal flow of a program.<br>
At the point where the exception occurs, some of the computations that the caller requested may have been done, while others remain undone.<br>
In general, bypassing part of the program might mean that an object is left in an invalid or incomplete state, or that a resource is not freed, and so on.<br>
Programs that properly “clean up” during exception handling are said to be exception safe.<br>
Writing exception safe code is surprisingly hard, and (largely) beyond the scope of this language Primer.<br>
Some programs use exceptions simply to terminate the program when an exceptional condition occurs.<br>
Such programs generally don’t worry about exception safety.<br>
Programs that do handle exceptions and continue processing generally must be constantly aware of whether an exception might occur and what the program must do to ensure that objects are valid, that resources don’t leak, and that the program is restored to an appropriate state.<br>
We will occasionally point out particularly common techniques used to promote exception safety.<br>
However, readers whose programs require robust exception handling should be aware that the techniques we cover are insufficient by themselves to achieve exception safety.