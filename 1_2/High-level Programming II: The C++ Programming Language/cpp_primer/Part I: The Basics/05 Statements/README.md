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