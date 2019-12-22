[TOC]

# 1.1. Vector Geometry and Algebra
* **vector** is a directional line that corresponds to a move from a point A to another point B ![vector](https://latex.codecogs.com/gif.download?%5Coverrightarrow%7BAB%7D)
* **initial point** / **tail** is the point A
* **terminal point** / **head** is the point B
* **component**s of a vector are its coordinates
* **row vector** ![row vector](https://latex.codecogs.com/gif.download?%5Cbegin%7Bpmatrix%7D%203%20%26%202%20%5Cend%7Bpmatrix%7D)
* **column vector** ![column vector](https://latex.codecogs.com/gif.download?%5Cbinom%7B3%7D%7B2%7D)
* Important part about the row and column vector is their components' **precedence**
* **zero vector** is a vector that starts and ends at the origin
* If two vectors have equal length and direction, the are **equal**
* A vector is at a **standard position** when its initial point as the origin

## Creating New Vector From Old Vector
* **vector addition** is the most fundamental operation out of all vector operations
* **sum** of two vectors:
> ![sum of vector](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D%20+%20%5Ctextup%7Bv%7D%20%3D%20%5Cbegin%7Bbmatrix%7D%20u_%7B1%7D%20+%20v_%7B1%7D%20%26%20u_%7B2%7D%20+%20v_%7B2%7D%20%5Cend%7Bbmatrix%7D)

### Initial to Terminal Point Rule
There are two vectors ![u](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D) and ![v](https://latex.codecogs.com/gif.download?%5Ctextup%7Bv%7D) in ![real space](https://latex.codecogs.com/gif.download?%5Cmathbb%7BR%7D%5E%7B2%7D). Translate v to make v's initial point ![u](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D)'s terminal point. Now, sum of ![u](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D) and ![v](https://latex.codecogs.com/gif.download?%5Ctextup%7Bv%7D), ![u + v](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D%20+%20%5Ctextup%7Bv%7D%20%3D%20%5Cbegin%7Bbmatrix%7D%20u_%7B1%7D%20+%20v_%7B1%7D%20%26%20u_%7B2%7D%20+%20v_%7B2%7D%20%5Cend%7Bbmatrix%7D) becomes a vector with ![u](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D)'s initial point to ![v](https://latex.codecogs.com/gif.download?%5Ctextup%7Bv%7D)'s terminal point.

### Parallelogram Rule
There are two vectors ![u](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D) and ![v](https://latex.codecogs.com/gif.download?%5Ctextup%7Bv%7D) in ![real space](https://latex.codecogs.com/gif.download?%5Cmathbb%7BR%7D%5E%7B2%7D). Then, the sum of vectors ![u + v](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D%20+%20%5Ctextup%7Bv%7D) is a diagonal vector of the parrallelogram determined by ![u](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D) and ![v](https://latex.codecogs.com/gif.download?%5Ctextup%7Bv%7D) in standard position.

* **scalar multiplication** is the second fundamental vector operation
> ![scalar multiplication](https://latex.codecogs.com/gif.download?c%5Ctextup%7Bv%7D%20%3D%20c%5Cbegin%7Bbmatrix%7D%20v_%7B1%7D%20%26%20v_%7B2%7D%20%5Cend%7Bbmatrix%7D%20%3D%20%5Cbegin%7Bbmatrix%7D%20cv_%7B1%7D%20%26%20cv_%7B2%7D%20%5Cend%7Bbmatrix%7D)

* **scalar** is a constant relevant to vectors
* Necessity and sufficiency for two vectors to be scalar product to each other is that two vectors are **parallel**
* **negative vector** is a scalar product between -1 and ![v](https://latex.codecogs.com/gif.download?%5Ctextup%7Bv%7D), which is used to define vector subtraction
* **difference** between ![u](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D) and ![v](https://latex.codecogs.com/gif.download?%5Ctextup%7Bv%7D):
> ![difference](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D%20-%20%5Ctextup%7Bv%7D%20%3D%20%5Ctextup%7Bu%7D%20+%20%28-%5Ctextup%7Bv%7D%29)
* difference of two vectors represent the other diagonal of the parallelogram

## Vector in ![n space](https://latex.codecogs.com/gif.download?%5Clarge%20%5Cmathbb%7BR%7D%5En)

### Theorem 1.1 Algebraic Characteristics of Vectors in ![n space](https://latex.codecogs.com/gif.download?%5Cmathbb%7BR%7D%5En)
![u](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%7D), ![v](https://latex.codecogs.com/gif.download?%5Ctextup%7Bv%7D), ![w](https://latex.codecogs.com/gif.download?%5Ctextup%7Bw%7D) are vectors in ![n space](https://latex.codecogs.com/gif.download?%5Cmathbb%7BR%7D%5En), and ![c](https://latex.codecogs.com/gif.download?c), ![d](https://latex.codecogs.com/gif.download?d) are scalars. Then,
1. ![commutative property](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%20+%20v%20%3D%20v%20+%20u%7D) (Commutative Property)
2. ![associative property](https://latex.codecogs.com/gif.download?%5Ctextup%7B%28u%20+%20v%29%20+%20w%20%3D%20u%20+%20%28v%20+%20w%29%7D) (Associative Property)
3. ![identity element](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%20+%200%20%3D%20u%7D) (Identity Element)
4. ![inverse element](https://latex.codecogs.com/gif.download?%5Ctextup%7Bu%20+%20%28-u%29%20%3D%200%7D
) (Inverse Element)
5. ![distributive property 1](https://latex.codecogs.com/gif.download?c%5Ctextup%7B%28u%20+%20v%29%20%3D%20%7Dc%5Ctextpup%7Bu%7D%20+%20c%5Ctextup%7Bv%7D) (Distributive Property)
6. ![distributive property 2](https://latex.codecogs.com/gif.download?%28c%20+%20d%29%5Ctextup%7Bu%7D%20%3D%20c%5Ctextup%7Bu%7D%20+%20d%5Ctextup%7Bu%7D) (Distributive Property)
7. ![c(du) = (cd)u](https://latex.codecogs.com/gif.download?c%28d%5Ctextup%7Bu%7D%29%20%3D%20%28cd%29%5Ctextup%7Bu%7D)
8. ![identity element](https://latex.codecogs.com/gif.download?1%5Ctextup%7Bu%7D%20%3D%20%5Ctextup%7Bu%7D) (Identity Element)

> **Warning**<br>
> Commutative Property and characteristic no 3 and 4 explains that ![](https://latex.codecogs.com/gif.download?0%20+%20%5Ctextup%7Bu%7D%20%3D%20%5Ctextup%7Bu%7D) and ![](https://latex.codecogs.com/gif.download?-%5Ctextup%7Bu%7D%20+%20%5Ctextup%7Bu%7D%20%3D%200)<br>
> if distributive property was understood in a direction from right to left, then it explains that such characteristics can be factorized by a common scalar or a common vector

## Linear Combination and Coordinate
### Definition
If scalar ![scalar](https://latex.codecogs.com/gif.download?c_%7B1%7D%2C%20c_%7B2%7D%2C%20%5Ccdots%20%2C%20c_%7Bk%7D) exists such that ![series](https://latex.codecogs.com/gif.download?%5Ctextup%7Bv%7D%20%3D%20c_%7B1%7D%5Ctextup%7Bv%7D_1%20+%20c_%7B2%7D%5Ctextup%7Bv%7D_2%20+%20%5Ccdots%20+%20c_%7Bk%7D%5Ctextup%7Bv%7D0_k), ![v](https://latex.codecogs.com/gif.download?%5Ctextup%7Bv%7D) is a **linear combination** of ![vectors](https://latex.codecogs.com/gif.download?%5Ctextup%7Bv%7D_1%2C%20%5Ctextup%7Bv%7D_2%2C%20%5Ccdots%20%2C%20%5Ctextup%7Bv%7D_k). The scalars ![scalar](https://latex.codecogs.com/gif.download?c_%7B1%7D%2C%20c_%7B2%7D%2C%20%5Ccdots%20%2C%20c_%7Bk%7D) are the **coefficient**s of the given linear combination.

## Binary Vector and Modulo Equation
* **Binary Vector** is a vector whose components are either 0 or 1
* Set of **Integers Modulo 2** is a set of scalars ![scalar](https://latex.codecogs.com/gif.download?%5Cbegin%7BBmatrix%7D%200%2C%261%20%5Cend%7BBmatrix%7D), also known as ![Zahlen](https://latex.codecogs.com/gif.download?%5Cmathbb%7BZ%7D_%7B2%7D), is a set with following parity rule:
	|+|0|1|
	|-|-|-|
	|0|0|1|
	|1|1|0|

	|·|0|1|
	|-|-|-|
	|0|0|0|
	|1|0|1|
	* ![Z](https://latex.codecogs.com/gif.download?%5Cmathbb%7BZ%7D_%7B2%7D%5E%7Bn%7D) is **closed** regarding the addition and multiplication operations
* **Binary Vectors of length** ![n](https://latex.codecogs.com/gif.download?n) are the vectors of ![Z](https://latex.codecogs.com/gif.download?%5Cmathbb%7BZ%7D_%7B2%7D%5E%7Bn%7D).
* Set of **integer modulo** ![m](https://latex.codecogs.com/gif.download?m) ![zm](https://latex.codecogs.com/gif.download?%5Cmathbb%7BZ%7D_%7Bm%7D) exists. A vector that has ![m](https://latex.codecogs.com/gif.download?m) pairs as its components is called ![m](https://latex.codecogs.com/gif.download?m)**-ary vector of length** ![n](https://latex.codecogs.com/gif.download?n).