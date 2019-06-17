## Warning
Readers should be aware that they must add appropriate `#include` and `using` declarations to our examples before compiling them.

## Note
In addition to specifying the operations that the library types provide, the standard also imposes efficiency requirements on implementors.<br>
As a result, library types are efficient enough for general use.

## Note
The newline that causes `getline` to return is discarded; the newline is not stored in the `string`.

## Tip
You can avoid problems due to conversion between `unsigned` and `int` by not using `int`s in expressions that use `size()`.

## Warning
For historical reasons, and for compatibility with C, string literals are not standard library strings.<br>
It is important to remember that these types differ when you use string literals and library strings.

## Advice: Use the C++ Versions of C Library Headers
In addition to facilities defined specifically for C++, the C++ library incorporates the C library.<br>
Headers in C have names of the form name `.h`.<br>
The C++ versions of these headers are named `c` name—they remove the `.h` suffix and precede the name with the letter `c`.<br>
The `c` indicates that the header is part of the C library.<br>
Hence, `cctype` has the same contents as `ctype.h`, but in a form that is appropriate for C++ programs.<br>
In particular, the names defined in the `c` name headers are defined inside the `std` namespace, whereas those defined in the `.h` versions are not.<br>
Ordinarily, C++ programs should use the `c` name versions of headers and not the name `.h` versions.<br>
That way names from the standard library are consistently found in the `std` namespace.<br>
Using the `.h` headers puts the burden on the programmer to remember which library names are inherited from C and which are unique to C++.

## Note
The values we use to subscript a `string` must be `>= 0` and `< size()`.<br>
**The result of using an index outside this range is undefined.**<br>
**By implication, subscripting an empty `string` is undefined.**

## Caution: Subscripts are Unchecked
When we use a subscript, we must ensure that the subscript is in range.<br>
That is, the subscript must be `>= 0` and `<` the `size()` of the string.<br>
One way to simplify code that uses subscripts is always to use a variable of type `string::size_type` as the subscript.<br>
Because that type is `unsigned`, we ensure that the subscript cannot be less than zero.<br>
When we use a `size_type` value as the subscript, we need to check only that our subscript is less than value returned by `size()`.

### Warning
The library is not required to check the value of an subscript.<br>
The result of using an out-of-range subscript is undefined.

## Note
`vector` is a template, not a type.<br>
Types generated from `vector` must include the element type, for example, `vector<int>`.

## Warning
Some compilers may require the old-style declarations for a `vector` of `vector`s, for example, `vector<vector<int> >`.

## Key Concept: vectors Grow Efficiently
The standard requires that `vector` implementations can efficiently add elements at run time.<br>
Because `vector`s grow efficiently, it is often unnecessary—and can result in poorer performance—to define a `vector` of a specific size.<br>
The exception to this rule is if all the elements actually need the same value.<br>
If differing element values are needed, it is usually more efficient to define an empty `vector` and add elements as the values we need become known at run time.<br>
Moreover, as we’ll see in § 9.4 (p. 355), `vector` offers capabilities to allow us to further enhance run-time performance when we add elements.<br>
Starting with an empty `vector` and adding elements at run time is distinctly different from how we use built-in arrays in C and in most other languages.<br>
In particular, if you are accustomed to using C or Java, you might expect that it would be best to define the `vector` at its expected size.<br>
In fact, the contrary is usually the case.

## Warning
The body of a range for must not change the size of the sequence over which it is iterating.

## Note
To use `size_type`, we must name the type in which it is defined. A `vector` type always includes its element type (§ 3.3, p. 97):
```
vector<int>::size_type // ok
vector::size_type      // error
```

## Warning
The subscript operator on `vector` (and `string`) fetches an existing element; it does not add an element.

## Caution: Subscript Only Elements that are Known to Exist!
It is crucially important to understand that we may use the subscript operator (the `[]` operator) to fetch only elements that actually exist.<br>
For example,
```
vector<int> ivec;      // empty vector
cout << ivec[0];       // error: ivec has no elements!
vector<int> ivec2(10); // vector with ten elements
cout << ivec2[10];     // error: ivec2 has elements 0 . . . 9
```
It is an error to subscript an element that doesn’t exist, but it is an error that the compiler is unlikely to detect.<br>
Instead, the value we get at run time is undefined.<br>
Attempting to subscript elements that do not exist is, unfortunately, an extremely common and pernicious programming error.<br>
So-called buffer overflow errors are the result of subscripting elements that don’t exist.<br>
Such bugs are the most common cause of security problems in PC and other applications.

### Tip
A good way to ensure that subscripts are in range is to avoid subscripting altogether by using a range for whenever possible.

## Note
If the container is empty, the iterators returned by begin and end are equal—they are both off-the-end iterators.

## Note
Because the iterator returned from `end` does not denote an element, it may not be incremented or dereferenced.

## Key Concept: Generic Programming
Programmers coming to C++ from C or Java might be surprised that we used `!=` rather than `<` in our for loops such as the one above and in the one on page 94.<br>
C++ programmers use `!=` as a matter of habit.<br>
They do so for the same reason that they use iterators rather than subscripts: This coding style applies equally well to various kinds of containers provided by the library.<br>
As we’ve seen, only a few library types, `vector` and `string` being among them, have the subscript operator.<br>
Similarly, all of the library containers have iterators that define the `==` and `!=` operators.<br>
Most of those iterators do not have the `<` operator.<br>
By routinely using iterators and `!=`, we don’t have to worry about the precise type of container we’re processing.

## Terminology: Iterators and Iterator Types
The term iterator is used to refer to three different entities.<br>
We might mean the concept of an iterator, or we might refer to the iterator type defined by a container, or we might refer to an object as an iterator.<br>
What’s important to understand is that there is a collection of types that are related conceptually.<br>
A type is an iterator if it supports a common set of actions.<br>
Those actions let us access an element in a container and let us move from one element to another.<br>
Each container class defines a type named iterator; that iterator type supports the actions of an (conceptual) iterator.

## Warning
For now, it is important to realize that loops that use iterators should not add elements to the container to which the iterators refer.

## Tip
If you don’t know exactly how many elements you need, use a `vector`.

## Warning
As with variables of built-in type, a default-initialized array of built-in type that is defined inside a function will have undefined values.

## Warning
Some compilers allow array assignment as a compiler extension.<br>
It is usually a good idea to avoid using nonstandard features.<br>
Programs that use such features, will not work with a different compiler.

## Tip
It can be easier to understand array declarations by starting with the array’s name and reading them from the inside out.

## Warning
The most common source of security problems are buffer overflow bugs.<br>
Such bugs occur when a program fails to check a subscript and mistakenly uses memory outside the range of an array or similar data structure.

## Note
In most expressions, when we use an object of array type, we are really using a pointer to the first element in that array.

## Note
A pointer “one past” the end of a built-in array behaves the same way as the iterator returned by the end operation of a `vector`.<br>
In particular, we may not dereference or increment an off-the-end pointer.

## Warning
Unlike subscripts for `vector` and `string`, the index of the built-in subscript operator is not an `unsigned` type.

## Warning
Although C++ supports C-style `string`s, they should not be used by C++ programs.<br>
C-style `string`s are a surprisingly rich source of bugs and are the root cause of many security problems.<br>
They’re also harder to use!