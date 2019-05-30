### Machine-Level Representation of the Built-in Types
Computers store data as a sequence of bits, each holding a 0 or 1, such as `00011011011100010110010000111011 ...`<br>
Most computers deal with memory as chunks of bits of sizes that are powers of 2.<br>
The smallest chunk of addressable memory is referred to as a **“byte.”**<br>
The basic unit of storage, usually a small number of bytes, is referred to as a **“word.”**<br>

On most machines a byte contains 8 bits and a word is either 32 or 64 bits, that is, 4 or 8 bytes.<br>
Most computers associate a number (called an “address”) with each byte in memory.<br>

## Advice: Deciding which Type to Use
C++, like C, is designed to let programs get close to the hardware when necessary.<br>
The arithmetic types are defined to cater to the peculiarities of various kinds of hardware.<br>
Most programmers can (and should) ignore these complexities by restricting the types they use.<br>
A few rules of thumb can be useful in deciding which type to use:
* **Use an unsigned type when you know that the values cannot be negative.**
* **Use int for integer arithmetic.** short is usually too small and, in practice, long often has the same size as int. If your data values are larger than the minimum guaranteed size of an int, then use long long.
* **Do not use plain char or bool in arithmetic expressions. Use them only to hold characters or truth values.** Computations using char are especially problematic because char is signed on some machines and unsigned on others. If you need a tiny integer, explicitly specify either signed char or unsigned char.
* **Use double for floating-point computations**; float usually does not have enough precision, and the cost of double-precision calculations versus single-precision is negligible. The precision offered by long double usually is unnecessary and often entails considerable run-time cost.

## Advice: Avoid Undefined and Implementation-Defined Behavior
**Undefined behavior** results from errors that the compiler is not required (and sometimes is not able) to detect.<br>
Even if the code compiles, a program that executes an undefined expression is in error.<br>
There is no guarantee that the same program, compiled under a different compiler or even a subsequent release of the same compiler, will continue to run correctly.<br>
Nor is there any guarantee that what works with one set of inputs will work with another.

Similarly, programs usually should avoid **implementation-defined behavior**, such as assuming that the size of an int is a fixed and known value.<br>
Such programs are said to be nonportable.<br>

Tracking down these sorts of problems in previously working programs is, mildly put, unpleasant.

## Caution: Don’t Mix Signed and Unsigned Types
Expressions that mix signed and unsigned values can yield surprising results when the signed value is negative.<br>
It is essential to remember that signed values are automatically converted to unsigned.

# Best Practices
**When you write a long literal, use the uppercase L; the lowercase letter l is too easily mistaken for the digit 1.**