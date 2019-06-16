# Machine-Level Representation of the Built-in Types
Computers store data as a sequence of bits, each holding a 0 or 1, such as `00011011011100010110010000111011 ...`<br>
Most computers deal with memory as chunks of bits of sizes that are powers of 2.<br>
The smallest chunk of addressable memory is referred to as a **“byte.”**<br>
The basic unit of storage, usually a small number of bytes, is referred to as a **“word.”**<br>

On most machines a byte contains 8 bits and a word is either 32 or 64 bits, that is, 4 or 8 bytes.<br>
Most computers associate a number (called an “address”) with each byte in memory.<br>

# Advice: Deciding which Type to Use
C++, like C, is designed to let programs get close to the hardware when necessary.<br>
The arithmetic types are defined to cater to the peculiarities of various kinds of hardware.<br>
Most programmers can (and should) ignore these complexities by restricting the types they use.<br>
A few rules of thumb can be useful in deciding which type to use:
* **Use an unsigned type when you know that the values cannot be negative.**
* **Use int for integer arithmetic.** `short` is usually too small and, in practice, `long` often has the same size as `int`. If your data values are larger than the minimum guaranteed size of an `int`, then use `long long`.
* **Do not use plain char or bool in arithmetic expressions. Use them only to hold characters or truth values.** Computations using `char` are especially problematic because `char` is signed on some machines and unsigned on others. If you need a tiny integer, explicitly specify either signed `char` or `unsigned char`.
* **Use double for floating-point computations**; `float` usually does not have enough precision, and the cost of double-precision calculations versus single-precision is negligible. The precision offered by `long double` usually is unnecessary and often entails considerable run-time cost.

# Advice: Avoid Undefined and Implementation-Defined Behavior
**Undefined behavior** results from errors that the compiler is not required (and sometimes is not able) to detect.<br>
Even if the code compiles, a program that executes an undefined expression is in error.<br>
There is no guarantee that the same program, compiled under a different compiler or even a subsequent release of the same compiler, will continue to run correctly.<br>
Nor is there any guarantee that what works with one set of inputs will work with another.

Similarly, programs usually should avoid **implementation-defined behavior**, such as assuming that the size of an `int` is a fixed and known value.<br>
Such programs are said to be nonportable.<br>

Tracking down these sorts of problems in previously working programs is, mildly put, unpleasant.

# Caution: Don’t Mix Signed and Unsigned Types
Expressions that mix signed and unsigned values can yield surprising results when the signed value is negative.<br>
It is essential to remember that signed values are automatically converted to unsigned.

# Best Practices
**When you write a long literal, use the uppercase L; the lowercase letter l is too easily mistaken for the digit 1.**

# Terminology: What is an Object?
**Most generally, an object is a region of memory that can contain data and has a type.**

# Warning
**Initialization is not assignment.**<br>
Initialization happens when a variable is given a value when it is created.<br>
Assignment obliterates an object’s current value and replaces that value with a new one.

# Note
Uninitialized objects of built-in type defined inside a function body have undefined value.<br>
Objects of class type that we do not explicitly initialize have a value that is defined by the class.

# Caution: Uninitialized Variables Cause Run-Time Problems
An uninitialized variable has an indeterminate value.<br>
Trying to use the value of an uninitialized variable is an error that is often hard to debug.<br>
What happens when we use an uninitialized variable is undefined.<br>

## Tip
We recommend initializing every object of built-in type.

# Note
Variables must be defined exactly once but can be declared many times.

# Key Concept: Static Typing
C++ is a statically typed language, which means that types are checked at compile time.<br>
The process by which types are checked is referred to as type checking.<br>
As we’ve seen, the type of an object constrains the operations that the object can perform.<br>
As our programs get more complicated, we’ll see that static type checking can help find bugs.<br>
However, a consequence of static checking is that the type of every entity we use must be known to the compiler.

# Best Practices
Naming conventions are most useful when followed consistently.

# Advice: Define Variables Where You First Use Them
Doing so improves readability by making it easy to find the definition of the variable.<br>
More importantly, it is often easier to give the variable a useful initial value when the variable is defined close to where it is first used.

# Warning
It is almost always a bad idea to define a local variable with the same name as a global variable that the function uses or might use.

# Note
A reference is not an object.<br>
Instead, a reference is just another name for an already existing object.

# Warning
Pointers are often hard to understand.<br>
Debugging problems due to pointer errors bedevil even experienced programmers.

# Note
We may dereference only a valid pointer that points to an object.<br>
## Key Concept: Some Symbols Have Multiple Meanings
Some symbols, such as `&` and `*`, are used as both an operator in an expression and as part of a declaration.

* In **declarations**, `&` and `*` are used to form compound types.
* In **expressions**, these same symbols are used to denote an operator.

# Advice: Initialize all Pointers
**Uninitialized pointers are a common source of run-time errors.**<br>
As with any other uninitialized variable, what happens when we use an uninitialized pointer is undefined.

If possible, define a pointer only after the object to which it should point has been defined.<br>
If there is no object to bind to a pointer, then initialize the pointer to `nullptr` or zero.

# Warning
Many programmers are confused by the interaction between the base type and the type modification that may be part of a declarator.

# Tip
There is no single right way to define pointers or references.<br>
The important thing is to choose a style and use it consistently.

# Tip
It can be easier to understand complicated pointer or reference declarations if you read them from right to left.

# Note
To share a const object among multiple files, you must define the variable as extern.

# Terminology: const Reference is a Reference to const
C++ programmers tend to abbreviate the phrase “reference to `const`” as “`const` reference.”<br>
This abbreviation makes sense—if you remember that it is an abbreviation.<br>
Technically speaking, there are no `const` references.<br>
A reference is not an object, so we cannot make a reference itself `const`.<br>
Indeed, because there is no way to make a reference refer to a different object, in some sense all references are `const`.<br>
Whether a reference refers to a `const` or non`const` type affects what we can do with that reference, not whether we can alter the binding of the reference itself.

# Tip
It may be helpful to think of pointers and references to const as pointers or references “that think they point or refer to `const`.” 12

# Best Practices
Generally, it is a good idea to use `constexpr` for variables that you intend to use as constant expressions.

# Warning
Remember that `decltype(( variable ))` (note, double parentheses) is always a reference type, but `decltype( variable )` is a reference type only if variable is a reference.

# Warning
It is a common mistake among new programmers to forget the semicolon at the end of a class definition.

# Note
Whenever a header is updated, the source files that use that header must be recompiled to get the new or changed declarations.

# Warning
Preprocessor variable names do not respect C++ scoping rules.

# Best Practices
Headers should have guards, even if they aren’t (yet) included by another header.
Header guards are trivial to write, and by habitually defining them you don’t need to decide whether they are needed.