# Problems

## 4-1 Recurrence examples

Give asymptotic upper and lower bounds for T(n) in each of the following recurrences. Assume that T(n) is constant for n &leq; 2. Make your bounds as tight as possible, and justify your answers.

### a. T(n) = 2T(n/2) + n<sup>4</sup>

a = 2, b = 2, f(n) = n<sup>4</sup>, n<sup>log<sub>2</sub>2</sup> = n = &Theta;(n)

f(n) = &Omega;(n<sup>1 + &eta;</sup>), &eta; = 3

T(n) = &Theta;(n<sup>4</sup>)

### T(n) = T(7n/10) + n

a = 1, b = 10/7, f(n) = n, n<sup>log<sub>10/7</sub>1</sup> = 1 = &Theta;(1)

7n/10 &leq; cn (c &leq; 7/10)

f(n) = &Omega;(n<sup>&eta;</sup>), &eta; = 1

T(n) = &Theta;(n)

### c. T(n) = 16T(n/4) + n<sup>2</sup>

a = 16, b = 4, f(n) = n<sup>2</sup>, n<sup>log<sub>4</sub>16</sup> = n<sup>2</sup> = &Theta;(n<sup>2</sup>)

T(n) = &Theta;(n<sup>2</sup>lgn)

### d. T(n) = 7T(n/3) + n<sup>2</sup>

a = 7, b = 3, f(n) = n<sup>2</sup>, n<sup>log<sub>3</sub>7</sup> = &Theta;(n<sup>log<sub>3</sub>7</sup>)

7(n/3)<sup>2</sup> = (7/9)n<sup>2</sup> &leq; cn<sup>2</sup> (c &leq; 7/9)

f(n) = &Omega;(n<sup>log<sub>3</sub>7</sup> + &eta;</sup>), &eta; = log<sub>3</sub>(9/7)

T(n) = &Theta;(n<sup>2</sup>)

### e. T(n) = 7T(n/2) + n<sup>2</sup>

a = 7, b = 2, f(n) = n<sup>2</sup>, n<sup>lg 7</sup> = &Theta;(n<sup>lg 7</sup>)

f(n) = O(n<sup>lg 7 - &eta;</sup>), &eta; = lg 7/4

T(n) = &Theta;(n<sup>lg 7</sup>)

### f. T(n) = 2T(n/4) + √n

a = 2, b = 4, f(n) = √n, n<sup>log<sub>4</sub>2</sup> = √n = &Theta;(√n)

T(n) = &Theta;(√n lg n)

### g. T(n) = T(n - 2) + n<sup>2</sup>

1. n<sup>2</sup>
2. (n - 2)<sup>2</sup>
3. (n - 2 \* 2)<sup>2</sup>
4. &hellip;
5. (n - 2 \* i)<sup>2</sup> = n<sup>2</sup> - 4in + 4i<sup>2</sup>

* T(n) = ∑<sub>i=0</sub><sup>n/2</sup>(n<sup>2</sup> - 4in + 4i<sup>2</sup>)
  * = n<sup>3</sup> / 2 + n<sup>2</sup>(n + 2) / 2 + n(n + 2)(n + 1) / 6
  * = &Theta;(n<sup>3</sup>)

## 4-2 Parameter-passing costs

Throughout this book, we assume that parameter passing during procedure calls takes constant time, even if an N -element array is being passed. This assumption is valid in most systems because a pointer to the array is passed, not the array itself. This problem examines the implications of three parameter-passing strategies:

1. An array is passed by pointer. Time = &Theta;(1).
2. An array is passed by copying. Time = &Theta;(N), where N is the size of the array.
3. An array is passed by copying only the subrange that might be accessed by the called procedure. Time = &Theta;(q - p + 1) if the subarray A[p..q] is passed.

### a

Consider the recursive binary search algorithm for finding a number in a sorted array (see Exercise 2.3-5). Give recurrences for the worst-case running times of binary search when arrays are passed using each of the three methods above, and give good upper bounds on the solutions of the recurrences. Let N be the size of the original problem and n be the size of a subproblem.

1. &Theta;(lg n)
2. &Theta;(n lg n)
3. &Theta;(n)

### b

Redo part (a) for the MERGE-SORT algorithm from Section 2.3.1.

1. &Theta;(n lg n)
2. &Theta;(n<sup>2</sup> lg n)
3. &Theta;(n lg n)

## 4-3 More recurrence examples

Give asymptotic upper and lower bounds for T(n) in each of the following recurrences. Assume that T(n) is constant for sufficiently small n. Make your bounds as tight as possible, and justify your answers.

### a. T(n) = 4T(n/3) + n lg n

a = 4, b = 3, f(n) = n lg n, n<sup>log<sub>3</sub>4</sup> = &Theta;(n<sup>log<sub>3</sub>4</sup>)

f(n) = O(n<sup>log<sub>3</sub>4 - &eta;</sup>), &eta; < log<sub>3</sub>(4 / 3)

T(n) = &Theta;(n<sup>log<sub>3</sub>4</sup>)

### b. T(n) = 3T(n/3) + n/lg n

1. n/lgn
2. ((n/3)/lg(n/3)) \* 3 = n/(lg n - lg 3)
3. n/((lg n - lg 3) - lg 3)
4. &hellip;
5. n/(lg n - i lg 3) = n/lg(n/3<sup>i</sup>)

* T(n) = n/lgn + n/(lgn - lg3) + n(lgn - 2lg3) + &hellip; n(lgn - log<sub>3</sub>n lg3)
  * = &Theta;(nlog<sub>3</sub>log<sub>3</sub>n)

### c. T(n) = 4T(n/2) + n<sup>2</sup>√n

a = 4, b = 2, f(n) = n<sup>5/2</sup>, n<sup>log<sub>2</sub>4</sup> = &Theta;(n<sup>2</sup>)

f(n) = &Omega;(n<sup>2 + &eta;</sup>) &eta; = 1/2

4(n/2)<sup>5/2</sup> = 2<sup>2 - 5/2</sup>n<sup>5/2</sup> &leq; cn<sup>5/2</sup>

2<sup>-1/2</sup> &leq; c < 1

T(n) = &Theta;(n<sup>5/2</sup>)

### d. T(n) = 3T(n/3 - 2) + n/2

T(n) = 3T(n/3) + n/2

a = 3, b = 3, f(n) = n/2, n<sup>log<sub>3</sub>3</sup> = n = &Theta;(n)

T(n) = &Theta;(n lg n)

### e. T(n) = 2T(n/2) + n/lg n

a = 2, b = 2, f(n) = n/lgn, n<sup>log<sub>2</sub>2</sup> = n = &Theta;(n)

f(n) = O(n<sup>1 - &eta;</sup>) ∄&eta;

1. n/lgn
2. ((n/2)lg(n-1)) * 2  = n/(lgn - 1)
3. n/(lgn - i)

* T(n) = n/lgn + n/(lgn - 1) + &hellip; + n = n/lg n + &hellip; + n/2 + n/1 (n = 2<sup>k</sup>)
  * = n&Theta;(lg lg n) = &Theta;(n lg lg n)

### f. T(n) = T(n/2) + T(n/4) + T(n/8) + n

assumption: T(n) &leq; cn

### g. T(n) = T(n - 1) + 1/n

1. 1/n
2. 1/(n - 1)
3. &hellip;
4. 1/(n - i)

* T(n) = 1/n + 1/(n - 1) + &hellip; + 1 + &Theta;(1) = &Theta;(lg n)
  * [https://en.wikipedia.org/wiki/Harmonic_number](https://en.wikipedia.org/wiki/Harmonic_number)

### h. T(n) = T(n - 1) + lg n

&Theta;(nlgn)

### i. T(n) = T(n - 2) + 1/lg n

assume &Theta;(n/lg n)

### j. T(n) = √nT(√n) + n

assume &Theta;(n lg lg n)

## 4-4 Fibonacci numbers

This problem develops properties of the Fibonacci numbers, which are defined by recurrence (3.22). We shall use the technique of generating functions to solve the Fibonacci recurrence. Define the generating function (or formal power series) F as

* F(z) ​= ∑<sub>i=0</sub><sup>∞</sup>​F<sub>i</sub>z<sup>i</sup>
  *  = 0 + z + z<sup>2</sup> + 2z<sup>3</sup> ⋯

where Fi is the i th Fibonacci number.

### a

Show that F(z) = z + zF(z) + z<sup>2</sup>F(z).

* z + z∑<sub>i=0</sub><sup>∞</sup>​F<sub>i</sub>z<sup>i</sup> + z<sup>2</sup>∑<sub>i=0</sub><sup>∞</sup>​F<sub>i</sub>z<sup>i</sup>
  * = z + ∑<sub>i=1</sub><sup>∞</sup>​F<sub>i - 1</sub>z<sup>i</sup> + ∑<sub>i=2</sub><sup>∞</sup>​F<sub>i - 2</sub>z<sup>i</sup>
  * = z + F<sub>0</sub>z + ∑<sub>i=2</sub><sup>∞</sup>(F<sub>i - 1</sub> + ​F<sub>i - 2</sub>)z<sup>i</sup>
  * = z + 0 + ∑<sub>i=2</sub><sup>∞</sup>(F<sub>i - 1</sub> + ​F<sub>i - 2</sub>)z<sup>i</sup>
  * = 0 + z + ∑<sub>i=2</sub><sup>∞</sup>(F<sub>i</sub>)z<sup>i</sup>
  * = F(z)

### b

Show that

* F(z) = z / (1−z−z<sup>2</sup>) ​
  * = z / (1−ϕz)(1−ϕ^​z)
  * = ​(1/(1−ϕz) − 1 /(1−ϕ^​z)​) / √5​

where

ϕ = (1+√5)/2 ​​= 1.61803…

and

ϕ^ = (1-√5)/2 ​​= −0.61803…

ϕ - ϕ^ = √5​
ϕ + ϕ^ = 1
ϕϕ^ = -1

* F(z) = F(z)(1 - z - z<sup>2</sup>)/(1 - z - z<sup>2</sup>)
  * = (F(z) - z + z - zF(z) - z<sup>2</sup>F(z))/(1 - z - z<sup>2</sup>)
  * = z/(1 - z - z<sup>2</sup>)
  * = z/(1 - (ϕ + ϕ^)z + ϕϕ^z<sup>2</sup>)
  * = z/((1−ϕz)(1−ϕ^​z))
  * = ((1 - ϕ^z) - (1 - ϕz))/(√5​(1−ϕz)(1−ϕ^​z))
  * = ​(1/(1−ϕz) − 1 /(1−ϕ^​z)​) / √5​

### c

Show that

F(z) = ∑<sub>i=0</sub><sup>∞</sup>(​(ϕ<sup>i</sup>−ϕ^​<sup>i</sup>)z<sup>i</sup>) / √5

1/(1 - x) = ∑<sub>i=0</sub><sup>∞</sup>x<sup>i</sup> (|x| < 1)

* F(z) = (1/(1−ϕz) − 1 /(1−ϕ^​z)​) / √5​
  * = (∑<sub>i=0</sub><sup>∞</sup>(ϕz)<sup>i</sup> - ∑<sub>i=0</sub><sup>∞</sup>(ϕ^​z)<sup>i</sup>) / √5​
  * = ∑<sub>i=0</sub><sup>∞</sup>(​(ϕ<sup>i</sup>−ϕ^​<sup>i</sup>)z<sup>i</sup>) / √5

d. Use part (c) to prove that F<sub>i</sub>=ϕ<sup>i</sup>/√5 for i > 0 , rounded to the nearest integer. (Hint: Observe that |ϕ^|​ < 1)

F(z) = ∑<sub>i=0</sub><sup>∞</sup>(​(ϕ<sup>i</sup>−ϕ^​<sup>i</sup>)z<sup>i</sup>) / √5

F<sub>i</sub> = (​(ϕ<sup>i</sup>−ϕ^​<sup>i</sup>)z<sup>i</sup>) / √5

* i = 1
  * ϕ / √5 > 0.5
* i > 2
  * |ϕ^| < 0.5

## 4-5 Chip testing

Professor Diogenes has n supposedly identical integrated-circuit chips that in principle are capable of testing each other. The professor’s test jig accommodates two chips at a time. When the jig is loaded, each chip tests the other and reports whether it is good or bad. A good chip always reports accurately whether the other chip is good or bad, but the professor cannot trust the answer of a bad chip. Thus, the four possible outcomes of a test are as follows:

Chip A says Chip B says Conclusion
B is good A is good both are good, or both are bad
B is good A is bad at least one is bad
B is bad A is good at least one is bad
B is bad A is bad at least one is bad

### a

Show that if more than n/2 chips are bad, the professor cannot necessarily determine which chips are good using any strategy based on this kind of pairwise test. Assume that the bad chips can conspire to fool the professor.

We can always find a set of good chips and set of bad chips of equal size.

Assume that bad chips "always" conspire

* if Good and Good,
  * good and good
* if Good and Bad
  * bad and bad
* if Bad and Good
  * bad and bad
* if Bad and Bad
  * good and good

thus, professors can't necessarily determine which chips are good or bad.

for example, if A and B yielded bad and bad, then either A or B is bad. if A and C yields good and good, A can both be good or bad.

* if A is good
  * B is bad, C is good
  * B and C should yield bad and bad
* if A is bad
  * B is good, C is bad
  * B and C should yield bad and bad

### b

Consider the problem of finding a single good chip from among n chips, assuming that more than n/2 of the chips are good. Show that ⌊n/2⌋ pairwise tests are sufficient to reduce the problem to one of nearly half the size.

put number of good chips as g, number of bad chips as b

* g + b = n, b &leq; g

1. Pick two chips, if n is odd, leave the remaining one
2. Test two chips, if at least one of them is bad, throw them
   * (g = g - 1 and b = b - 1) or (b = b - 2)
   * Thus, g &geq; b
3. Iterate until two or one chips remain.
   1. if there is only one remaining, it is the good chip.
   2. if there are two chips remaining, test them. just like in step 2, throw away if one of them is bad
      * if thrown away, then the remaining chip is the good one.

### c

Show that the good chips can be identified with &Theta;(n) pairwise tests, assuming that more than n/2 of the chips are good. Give and solve the recurrence that describes the number of tests.

using b,

T(n) &leq; T(⌈n/2⌉) + ⌊n/2⌋.

* n is even

a = 1, b = 2, f(n) = n/2, n<sup>log<sub>2</sub>1</sup> = 1 = &Theta;(1)

f(n) = &Omega;(n<sup>&eta;</sup>), eta = 1/2

((n/2)/2) = n / 4 &leq; cn/2 (1/2 &leq; c < 1)

T(n) &leq; &Theta;(n)
T(n) = O(n)

After finding a good chip, we can identify all good chips with that among the n - 1 tests.

T(n) = O(n) + n - 1 = &Theta;(n)

## 4-6 Monge arrays

An m × n array A of real numbers is a Monge array if for all i, j, k, and l such that 1 &leq; i < k &leq; m and 1 &leq; j < l &leq; n, we have

A[i,j] + A[k,l] ≤ A[i,l] + A[k,j]

In other words, whenever we pick two rows and two columns of a Monge array and consider the four elements at the intersections of the rows and the columns, the sum of the upper-left and lower-right elements is less than or equal to the sum of the lower-left and upper-right elements. For example, the following array is Monge:

<table>
	<tbody>
		<td>
			<tr>10</tr>
			<tr>17</tr>
			<tr>13</tr>
			<tr>28</tr>
			<tr>23</tr>
		</td>
		<td>
			<tr>17</tr>
			<tr>22</tr>
			<tr>16</tr>
			<tr>29</tr>
			<tr>23</tr>
		</td>
		<td>
			<tr>24</tr>
			<tr>28</tr>
			<tr>22</tr>
			<tr>34</tr>
			<tr>24</tr>
		</td>
		<td>
			<tr>11</tr>
			<tr>13</tr>
			<tr>6</tr>
			<tr>17</tr>
			<tr>7</tr>
		</td>
		<td>
			<tr>45</tr>
			<tr>44</tr>
			<tr>32</tr>
			<tr>37</tr>
			<tr>23</tr>
		</td>
		<td>
			<tr>36</tr>
			<tr>33</tr>
			<tr>19</tr>
			<tr>21</tr>
			<tr>6</tr>
		</td>
		<td>
			<tr>75</tr>
			<tr>66</tr>
			<tr>51</tr>
			<tr>53</tr>
			<tr>34</tr>
		</td>
	</tbody>
</table>

### a

Prove that an array is Monge if and only if for all i = 1,2,…,m−1 and j = 1, 2, …, n−1, we have

A[i, j] + A[i+1, j+1] ≤ A[i, j+1] + A[i+1, j]

(Hint: For the “if” part, use induction separately on rows and columns.)

#### left to right

trivial

#### right to left

A[i, j] + A[i+1, j+1] ≤ A[i, j+1] + A[i+1, j] (k = i + 1, l = j + 1)
A[i, j] + A[k, j+1] ≤ A[i, j+1] + A[k, j]
A[k, j] + A[k+1, j+1] ≤ A[k, j+1] + A[k+1, j]
A[i, j] + A[k, j+1] + A[k, j] + A[k+1, j+1] ≤ A[i, j+1] + A[k, j] + A[k, j+1] + A[k+1, j]
A[i, j] + A[k+1, j+1] ≤ A[i, j+1] + A[k+1, j]

this assumption can be extended

### b

The following array is not Monge. Change one element in order to make it Monge. (Hint: Use part (a).)

37 23 22 32
21 6 7 10
53 34 30 31
32 13 9 6
43 21 15 8

change 22 to 24

### c

Let f(i) be the index of the column containing the leftmost minimum element of row i. Prove that f(1) &leq; f(2) &leq; &hellip; &leq; f(m) for any m × n Monge array.

put a<sub>i</sub>, b<sub>j</sub> the leftmost minimum elements of row i and j, such that i > j

A[j, a] + A[i, b] &leq; A[i, a] + A[j, b]

but,

* A[j,a] ≥ A[i,a] ​(a<sub>i</sub> is minimal)
* A[i,b] ≥ A[j,b] (b<sub>j</sub> is minimal)​

thus,

* A[j, a] + A[i, b] ​≥ A[i, a] + A[j, b]
* A[j, a] + A[i, b] = A[i, a] + A[j, b]

* A[j, b] < A[i, b] ⇒ A[i, a] > A[j, a] ⇒ a<sub>i</sub> is not minimum, or
* A[j, b] = A[i, b]​ ⇒ A[i, a] > A[j, a] ⇒ b<sub>j</sub> is not the leftmost minimum

### d

Here is a description of a divide-and-conquer algorithm that computes the leftmost minimum element in each row of an m × n Monge array A:

Construct a submatrix A' of A consisting of the even-numbered rows of A. Recursively determine the leftmost minimum for each row of A'. Then  compute the leftmost minimum in the odd-numbered rows of A.

Explain how to compute the leftmost minimum in the odd-numbered rows of A (given that the leftmost minimum of the even-numbered rows is known) in O(m + n) time.

put a<sub>i</sub> as the index of the column of the leftmost mininum of row i.

if i is odd, then we know the value of a<sub>i - 1</sub>, a<sub>i + 1</sub>, and a<sub>i - 1</sub> &leq; a<sub>i</sub> &leq; a<sub>i + 1</sub>.

Thus, in order to know each a<sub>i</sub>, we need to iterate maximum a<sub>i + 1</sub> - a<sub>i - 1</sub> + 1 elements.

* T(n) = ∑<sub>i = 0</sub><sup>m/2 - 1</sup>(a<sup>2i + 2</sup> - a<sub>2i</sub> + 1)
  * = ∑<sub>i = 0</sub><sup>m/2 - 1</sup>(a<sup>2i + 2</sup>) - ∑<sub>i = 0</sub><sup>m/2 - 1</sup>(a<sub>2i</sub>) + m/2
  * = ∑<sub>i = 1</sub><sup>m/2</sup>(a<sup>2i</sup>) - ∑<sub>i = 0</sub><sup>m/2 - 1</sup>(a<sub>2i</sub>) + m/2
  * = m/2 - a<sub>0</sub> + a<sub>m</sub>
  * = n + m/2
  * = O(m + n)

### e

Write the recurrence describing the running time of the algorithm described in part (d). Show that its solution is O(m + n log m)

divide: O(1)
conquer: T(m/2)
merge: O(m + n)

* T(m) = O(1) + T(m/2) + O(m + n)
  * = T(m/2) + cm + dn

1. cm + dn
2. c(m/2) + dn
3. &hellip;
4. c(m/2<sup>i</sup>) + dn

* T(m) = ∑<sub>i = 0</sub><sup>lg m - 1</sup>(cn + d(m/2<sup>i</sup>))
  * = cn lg m + ∑<sub>i = 0</sub><sup>lg m - 1</sup>d(m/2<sup>i</sup>)
  * = cn lg m + 2dm(1 - (1/2)<sup>lg m</sup>)
  * < cn lg m + 2dm
  * = O(n lg m + m)