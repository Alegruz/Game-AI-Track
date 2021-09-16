# Exercises

## 4.1-1

What does FIND-MAXIMUM-SUBARRAY return when all elements of A are negative?

returns the largest element.

## 4.1-2

Write pseudocode for the brute-force method of solving the maximum-subarray problem. Your procedure should run in &Theta;(n<sup>2</sup>) time.

```
n = A.length
max-sum = -∞
for i = 1 to n
	sum = 0
	for j = i to n
		sum = sum + A[j]
		if sum > max-sum
			max-sum = sum
			low = i
			high = h
return (low, high, max-sum)
```

## 4.1-3

Implement both the brute-force and recursive algorithms for the maximum-subarray problem on your own computer. What problem size n<sub>0</sub> gives the crossover point at which the recursive algorithm beats the brute-force algorithm? Then, change the base case of the recursive algorithm to use the brute-force algorithm whenever the problem size is less than n<sub>0</sub>. Does that change the crossover point?

220.

no.

## 4.1-4

Suppose we change the definition of the maximum-subarray problem to allow the result to be an empty subarray, where the sum of the values of an empty subarray is 0. How would you change any of the algorithms that do not allow empty subarrays to permit an empty subarray to be the result?

## 4.1-5

Use the following ideas to develop a nonrecursive, linear-time algorithm for the maximum-subarray problem. Start at the left end of the array, and progress toward the right, keeping track of the maximum subarray seen so far. Knowing a maximum subarray of A[1&hellip;j], extend the answer to find a maximum subarray ending at index j + 1 by using the following observation: a maximum subarray of A[1&hellip;j + 1] is either a maximum subarray of A[1&hellip;j] or a subarray A[i&hellip;j + 1], for some 1 &leq; i &leq; j + 1. Determine a maximum subarray of the form A[i&hellip;j + 1] in constant time based on knowing a maximum subarray ending at index j.

```
max_sum = -∞
sum = -∞
max_low = low
max_high = high
for i = low to high
	current_high = i
	if sum > 0
		sum = sum + A[i]
	else
		current_low = i
		sum = A[i]
	if sum > max_sum
		max_sum = sum
		max_low = current_low
		max_high = current_high

return (max_low, max_high, max_sum)
```

## 4.2-1

Use Strassen’s algorithm to compute the matrix product

(1 3) (6 8)
(7 5) (4 2)

Show your work.

S<sub>1</sub> = 8 - 2 = 6
S<sub>2</sub> = 1 + 3 = 4
S<sub>3</sub> = 7 + 5 = 12
S<sub>4</sub> = 4 - 6 = -2
S<sub>5</sub> = 1 + 5 = 6
S<sub>6</sub> = 6 + 2 = 8
S<sub>7</sub> = 3 - 5 = -2
S<sub>8</sub> = 4 + 2 = 6
S<sub>9</sub> = 1 - 7 = -6
S<sub>10</sub> = 6 + 8 = 14

P<sub>1</sub> = 1 * 6 = 6
P<sub>2</sub> = 4 * 2 = 8
P<sub>3</sub> = 12 * 6 = 72
P<sub>4</sub> = 5 * -2 = -10
P<sub>5</sub> = 6 * 8 = 48
P<sub>6</sub> = -2 * 6 = -12
P<sub>7</sub> = -6 * 14 = -84

C<sub>11</sub> = 48 - 10 - 8 - 12 = 18
C<sub>12</sub> = 6 + 8 = 14
C<sub>21</sub> = 72 - 10 = 62
C<sub>22</sub> = 48 + 6 - 72 + 84 = 66

## 4.2-2

Write pseudocode for Strassen’s algorithm.

### `STRASSEN(A, B)`

```
n = A.rows
if n == 1
	return A[1, 1] * B[1, 1]
let C be a new n * n matrix
A[1, 1] = A[1..n/2][1..n/2]
A[1, 2] = A[1..n/2][n/2 + 1..n]
A[2, 1] = A[n/2 + 1..n][1..n/2]
A[2, 2] = A[n/2 + 1..n][n/2 + 1..n]
B[1, 1] = B[1..n/2][1..n/2]
B[1, 2] = B[1..n/2][n/2 + 1..n]
B[2, 1] = B[n/2 + 1..n][1..n/2]
B[2, 2] = B[n/2 + 1..n][n/2 + 1..n]
S[1] = B[1, 2] - B[2, 2]
S[2] = A[1, 1] + A[1, 2]
S[3] = A[2, 1] + A[2, 2]
S[4] = B[2, 1] - B[1, 1]
S[5] = A[1, 1] + A[2, 2]
S[6] = B[1, 1] + B[2, 2]
S[7] = A[1, 2] - A[2, 2]
S[8] = B[2, 1] + B[2, 2]
S[9] = A[1, 1] - A[2, 1]
S[10] = B[1, 1] + B[1, 2]
P[1] = STRASSEN(A[1, 1], S[1])
P[2] = STRASSEN(S[2], B[2, 2])
P[3] = STRASSEN(S[3], B[1, 1])
P[4] = STRASSEN(A[2, 2], S[4])
P[5] = STRASSEN(S[5], S[6])
P[6] = STRASSEN(S[7], S[8])
P[7] = STRASSEN(S[9], S[10])
C[1..n / 2][1..n / 2] = P[5] + P[4] - P[2] + P[6]
C[1..n / 2][n / 2 + 1..n] = P[1] + P[2]
C[n / 2 + 1..n][1..n / 2] = P[3] + P[4]
C[n / 2 + 1..n][n / 2 + 1..n] = P[5] + P[1] - P[3] - P[7]

return C
```

## 4.2-3

How would you modify Strassen’s algorithm to multiply n × n matrices in which n is not an exact power of 2? Show that the resulting algorithm runs in time Θ(n<sup>lg 7</sup>).

pad them to fit the size exact to power of 2.

## 4.2-4

What is the largest k such that if you can multiply 3 × 3 matrices using k multiplications (not assuming commutativity of multiplication), then you can multiply n × n matrices in time o(n<sup>lg 7</sup>)? What would the running time of this algorithm be?

assume n = 3<sup>m</sup>

T(n) = kT(n / 3) + O(1)

log<sub>3</sub>k < lg 7
k = 21

## 4.2-5

V. Pan has discovered a way of multiplying 68 × 68 matrices using 132,464 multiplications, a way of multiplying 70 × 70 matrices using 143,640 multiplications, and a way of multiplying 72 × 72 matrices using 155,424 multiplications. Which method yields the best asymptotic running time when used in a divide-and-conquer matrix-multiplication algorithm? How does it compare to Strassen’s algorithm?

log<sub>68</sub>132464 ≈ 2.795128
log<sub>70</sub>143640 ≈ 2.795122
log<sub>72</sub>155424 ≈ 2.795147.​

70 × 70 method.

## 4.2-6

How quickly can you multiply a kn × n matrix by an n × kn  matrix, using Strassen’s algorithm as a subroutine? Answer the same question with the order of the input matrices reversed.

kn × n \* n × kn -> k<sup>2</sup> multiplications of n × n matrices
n × kn \* kn × n -> k multiplications and k - 1 additions

## 4.2-7

Show how to multiply the complex numbers a + bi and c + di  using only three multiplications of real numbers. The algorithm should take a, b, c, and d as input and produce the real component ac - bd and the imaginary component ad + bc separately

* (a + bi)(c + di) = ac + adi + cbi - bd (4 mult) = (ac - bd) + (ad + cb)i (2 adds)
  * S<sub>1</sub> = (a - b) (c - d) = ac - ad - bc + bd
  * S<sub>2</sub> = ac
  * S<sub>3</sub> = bd
  * (S<sub>2</sub> - S<sub>3</sub>) + (S<sub>1</sub> - S<sub>2</sub> - S<sub>3</sub>)i

## 4.3-1

Show that the solution of T(n) = T(n - 1) + n is O(n<sup>2</sup>).

T(2) = T(1) + 2
T(3) = T(2) + 3
&hellip;
T(n) = T(n - 1) + n

T(n) = T(1) + (n(n + 1) / 2) - 1 = O(n<sup>2</sup>)

## 4.3-2

Show that the solution of T(n) = T(⌈n/2⌉) + 1 is O(lg n).

T(n) &leq; clg(n - a) ??

* T(n) = T(⌈n/2⌉) + 1 &leq; clg(⌈n/2⌉ - a) + 1
  * n is even
    * = clg (n / 2 - a) + 1
    * = clg((n - 2a)/2)
    * = clg(n - 2a) - c + 1
    * &leq; clg(n - 2a)
    * &leq; clg(n - a)
  * n is odd
    * = clg ((n + 1)/ 2 - a) + 1
    * = clg((n + 1 - 2a)/2)
    * = clg(n + 1 - 2a) - c + 1
    * &leq; clg(n + 1 - 2a)
    * &leq; clg(n - a)

## 4.3-3

We saw that the solution of T(n) = 2T(⌊n/2⌋) + n is O(n lg n). Show that the solution of this recurrence is also &Omega;(n lg n). Conclude that the solution is &Theta;(n lg n).

T(n) &leq; cn lg n

* T(n)​ ≤ 2c⌊n/2⌋lg⌊n/2⌋ + n
  * ≤ cnlg(n/2) + n
  * = cnlgn − cnlg2 + n
  * = cnlgn + (1 − c)n
  * ≤ cnlgn (c &geq; 1)

T(n) &geq; c(n + a)lg(n + a)

* T(n)​ ≥ 2c(⌊n/2⌋ + a)(lg(⌊n/2⌋ + a) + n
  * ≥ 2c((n−1)/2 + a)(lg((n−1)/2 + a)) + n
  * = 2c((n−1+2a)/2)​lg(n−1+2a​)/2 + n
  * = c(n−1+2a)lg(n−1+2a) − c(n−1+2a)lg2 + n
  * = c(n−1+2a)lg(n−1+2a) + (1−c)n − (2a−1)c (0 &leq; c < 1, n &geq; (2a - 1)c/(1-c))
  * ≥ c(n−1+2a)lg(n−1+2a) (a &geq; 1)
  * ≥ c(n+a)lg(n+a)

## 4.3-4

Show that by making a different inductive hypothesis, we can overcome the difficulty with the boundary condition T(1) = 1 for recurrence (4.19) without adjusting the boundary conditions for the inductive proof.

T(n) &leq; nlgn + n

* T(n) ≤ 2(c⌊n/2⌋lg⌊n/2⌋ + ⌊n/2⌋) + n
  * ≤ 2c(n/2)lg(n/2) + 2(n/2) + n
  * = cnlg(n/2) + 2n
  * = cnlgn − cnlg2 + 2n
  * = cnlgn + (2−c)n
  * ≤ cnlgn + n (c &geq; 1)

​T(1) = 1 &leq; cnlgn + n = 0 + 1 = 1

## 4.3-5

Show that &Theta;(n lg n) is the solution to the “exact” recurrence (4.3) for merge sort.

prove. O(nlgn)

O(nlgn), T(n) ≤ c(n−2)lg(n−2)

* T(n)​ ≤ c(⌈n/2⌉ − 2)lg(⌈n/2⌉ − 2) + c(⌊n/2⌋ − 2)lg(⌊n/2⌋ − 2) + dn
  * ≤ c(n/2+1−2)lg(n/2+1−2) + c(n/2−2)lg(n/2−2) + dn
  * ≤ c(n/2−1)lg(n/2−1) + c(n/2−1)lg(n/2−1) + dn
  * = c((n − 2)/2)​lg((n − 2)/2) ​+ c((n − 2)/2)​lg((n−2)/2) ​+ dn
  * = c(n−2)lg((n−2)/2)​ + dn
  * = c(n−2)lg(n−2) − c(n−2) + dn
  * = c(n−2)lg(n−2) + (d−c)n + 2c
  * ≤ c(n−2)lg(n−2) (c > d)

prove. &Omega;(nlgn)

&Omega;(nlgn), T(n)≥c(n+2)lg(n+2)

* T(n) ​≥ c(⌈n/2⌉+2)lg(⌈n/2⌉+2) + c(⌊n/2⌋+2)lg(⌊n/2⌋+2) + dn
  * ≥ c(n/2+2)lg(n/2+2) + c(n/2−1+2)lg(n/2−1+2) + dn
  * ≥ c(n/2+1)lg(n/2+1) + c(n/2+1)lg(n/2+1) + dn
  * ≥ c((n+2)/2)​lg((n+2/2)​ + c((n+2)/2)​lg((n+2)/2) ​+ dn
  * = c(n+2)lg((n+2)/2) ​+ dn
  * = c(n+2)lg(n+2) − c(n+2) + dn
  * = c(n+2)lg(n+2) + (d−c)n − 2c
  * ≥ c(n+2)lg(n+2) (d > c)

## 4.3-6

Show that the solution to T(n) = 2T(⌊n/2⌋+ 17) + n is O(n lg n).

T(n) ≤ c(n−a)lg(n−a)

* T(n)​ ≤ 2c(⌊n/2⌋+17−a)lg(⌊n/2⌋+17−a) + n
  * ≤ 2c(n/2+17−a)lg(n/2+17−a) + n
  * = c(n+34−2a)lg((n+34−2a​)/2) + n
  * = c(n+34−2a)lg(n+34−2a) − c(n+34−2a) + n (c > 1, n > n<sub>0</sub> = f(a))
  * ≤ c(n+34−2a)lg(n+34−2a) (a &geq; 34)
  * ≤ c(n−a)lg(n−a)

## 4.3-7

Using the master method in Section 4.5, you can show that the solution to the recurrence T(n) =  4T(n/3) + n is T(n) = &Theta;(n<sup>log<sub>3</sub>4</sup>). Show that a substitution proof with the assumption T(n) &leq; cn<sup>log<sub>3</sub>4</sup> fails. Then show how to subtract off a lower-order term to make a substitution proof work.

T(n) ≤ cn<sup>log<sub>3</sub>4</sup>

* T(n) ​≤ 4c(n/3)<sup>log<sub>3</sub>4</sup> + n
  * = cn<sup>log<sub>3</sub>4</sup>+n.

try T(n) ≤ cn<sup>log<sub>3</sub>4</sup> - dn

* T(n)​ ≤ 4(c(n/3)<sup>log<sub>3</sub>4</sup>−dn/3) + n
  * = 4(cn<sup>log<sub>3</sub>4</sup>/4−dn/3) + n
  * = cn<sup>log<sub>3</sub>4</sup> − (4/3)​dn + n
  * ≤ cn<sup>log<sub>3</sub>4</sup> − dn (d &geq; 3)

## 4.3-8

Using the master method in Section 4.5, you can show that the solution to the recurrence T(n) = 4T(n/2) + n<sup>2</sup> is T(n) = &Theta;(n<sup>2</sup>). Show that a substitution proof with the assumption T(n) &leq; cn<sup>2</sup> fails. Then show how to subtract off a lower-order term to make a substitution proof work.

T(n) ≤ cn<sup>2</sup>

* T(n)​ = 4T(n/2) + n
  * ≤ 4c(n/2)<sup>2</sup> + n
  * = cn<sup>2</sup> + n

try T(n) ≤ cn<sup>2</sup> - cn

* T(n)​ = 4T(n/2) + n
  * = 4(c(n/2)<sup>2</sup>−c(n/2)) + n
  * = 4c(n/2)<sup>2</sup>−4c(n/2) + n
  * = cn<sup>2</sup> + (1−2c)n
  * ≤ cn<sup>2</sup> (c &geq; 1/2)​

## 4.3-9

Solve the recurrence T(n) = 3T(√n) + log n by making a change of variables. Your solution should be asymptotically tight. Do not worry about whether values are integral

T(n) ​= 3T(n​) + lgn (let m = lgn)
T(2m) = 3T(2m/2) + m
S(m) = 3S(m/2) + m

S(m) ≤ cm<sup>lg3</sup> + dm

* S(m) ​≤ 3(c(m/2)<sup>lg3</sup> + d(m/2)) + m
  * ≤ cm<sup>lg3</sup> + ((3/2)​d+1)m (d &leq; -2)
  * ≤ cm<sup>lg3</sup> + dm

S(m) &geq; cm<sup>lg3</sup> + dm

* S(m) ​&geq; 3(c(m/2)<sup>lg3</sup> + d(m/2)) + m
  * &geq; cm<sup>lg3</sup> + ((3/2)​d+1)m (d &geq; -2)
  * &geq; cm<sup>lg3</sup> + dm

S(m) ​= Θ(m<sup>lg3</sup>)
T(n) = Θ(lg<sup>lg3</sup>n)

## 4.4-1

Use a recursion tree to determine a good asymptotic upper bound on the recurrence T(n) = 3T(⌊n/2⌋)) + n. Use the substitution method to verify your answer.

1. n
2. (⌊n/2⌋) * 3
3. (⌊⌊n/2⌋/2⌋) * 9
4. &hellip;
5. (n is even) (n/2<sup>i</sup>) * 3<sup>i</sup>
   (n is odd) ((n - 1)/2<sup>i</sup>) * 3<sup>i</sup>

* T(n) = n + (3/2)<sup>1</sup>n + &hellip; (3/2)<sup>lg n - 1</sup>n + &Theta;(n<sup>lg 3</sup>)
  * = (((3/2)<sup>lg n</sup> - 1)/((3/2) - 1))n + &Theta;(n<sup>lg 3</sup>)
  * = 2((3/2)<sup>lg n</sup> - 1)n + &Theta;(n<sup>lg 3</sup>)
  * = 2(n<sup>lg3</sup>) + &Theta;(n<sup>lg 3</sup>)
  * = O(n<sup>lg3</sup>)

T(n)≤ cn<sup>lg 3</sup> − dn

* T(n)​ = 3T(⌊n/2⌋) + n
  * ≤ 3⋅(c(n/2)<sup>lg 3</sup> − d(n/2)) + n
  * = (3/2<sup>lg 3</sup>)cn<sup>lg 3</sup> − (3d/2)n + n
  * = cn<sup>lg 3</sup> + (1−3d/2)n (d &geq; 2)

## 4.4-2

Use a recursion tree to determine a good asymptotic upper bound on the recurrence T(n) = T(n/2) + n<sup>2</sup>. Use the substitution method to verify your answer.

1. n<sup>2</sup>
2. (n/2)<sup>2</sup>
3. &hellip;
4. (n/2<sup>i</sup>)<sup>2</sup>

* T(n) = n<sup>2</sup> + (n/2)<sup>2</sup> + &hellip; + (n/2<sup>lg n - 1</sup>)<sup>2</sup> + &Theta;(1)
  * < n<sup>2</sup> + (n/2)<sup>2</sup> + &hellip; + (n/2<sup>lg n - 1</sup>)<sup>2</sup> + &hellip; (to inf) + &Theta;(1)
  * = n<sup>2</sup>/1 - (1/4) + &Theta;(1)
  * = (4/3)n<sup>2</sup> + &Theta;(1)
  * = &Theta;(n<sup>2</sup>)

T(n) ≤ cn<sup>2</sup>

* T(n)​ ≤ c(n/2)<sup>2</sup> + n<sup>2</sup>
  * = cn<sup>2</sup>/4 + n<sup>2</sup>
  * = (c/4+1)n<sup>2</sup>
  * ≤ cn<sup>2</sup>​ (c &geq; 4/3)

## 4.4-3

Use a recursion tree to determine a good asymptotic upper bound on the recurrence T(n) = 4T(n/2 + 2) + n. Use the substitution method to verify your answer.

1. n
2. (n/2 + 2) * 4
3. ((n/2 + 2)/2 + 2) * 4 = (n/2<sup>2</sup> + 2<sup>0</sup> + 2) * 4
4. (((n/2 + 2)/2 + 2)/2 + 2) * 16 = ((n/2<sup>2</sup> + 2<sup>0</sup> + 2)/2 + 2) = (n/2<sup>3</sup> + 2<sup>-1</sup> + 2<sup>0</sup> + 2<sup>1</sup>) * 16
5. &hellip;
6. (n/2<sup>i</sup> + 2<sup>1</sup> + 2<sup>0</sup> + &hellip; + 2<sup>2 - i</sup>)

* T(n) = ∑<sub>i=0</sub><sup>lgn−1​</sup>(2<sup>i</sup>n+2⋅4<sup>i</sup>) + Θ(n<sup>2</sup>)
  * =	∑<sub>i=0</sub><sup>lgn−1​</sup>2<sup>i</sup>>n + ∑<sub>i=0</sub><sup>lgn−1​</sup>2⋅4<sup>i</sup> + Θ(n<sup>2</sup>)
  * = (2<sup>lgn</sup>−1)​n + 2⋅(4<sup>lgn</sup>−1)/(4-3) ​+ Θ(n<sup>2</sup>)
  * = (2<sup>lgn</sup>−1)n + (2/3)​(4<sup>lgn</sup>−1) + Θ(n<sup>2</sup>)
  * = (n−1)n + (2/3)​(n<sup>2</sup>−1) + Θ(n<sup>2</sup>)
  * = Θ(n<sup>2</sup>)

## 4.4-4

Use a recursion tree to determine a good asymptotic upper bound on the recurrence T(n) = 2T(n - 1) + 1. Use the substitution method to verify your answer.

1. 1
2. 1 * 2
3. &hellip;
4. 1 * 2<sup>i</sup>

* T(n) = ∑<sub>i=0</sub><sup>n−1</sup>​2<sup>i</sup>
  * = 2<sup>n</sup>−1​
  * = Θ(2<sup>n</sup>)

## 4.4-5

Use a recursion tree to determine a good asymptotic upper bound on the recurrence T(n) = T(n - 1) + T(n/2) + n. Use the substitution method to verify your answer.

assume O(2<sup>n</sup>) and &Omega;(n<sup>n</sup>)

substitution method:

T(n) ≤ c2<sup>2</sup> − 4n
T(n)≥ cn<sup>2</sup>

## 4.4-6

Argue that the solution to the recurrence T(n) = T(n/3) + T(2n/3) + cn, where c is a constant, is &Omega;(n lg n) by appealing to a recursion tree.

1. cn
2. cn/3 | 2cn/3
3. cn/9 | 2cn/9 | 2cn/9 | 4cn/9 

## 4.4-7

Draw the recursion tree for T(n) D 4T .bn=2c/ Ccn, where c is a constant, and provide a tight asymptotic bound on its solution. Verify your bound by the substitution method.

## 4.4-8

Use a recursion tree to give an asymptotically tight solution to the recurrence T(n) = T .n a/ CT .a/ Ccn, where a 1 and c > 0 are constants.

## 4.4-9

Use a recursion tree to give an asymptotically tight solution to the recurrence T(n) = T . ̨ n/ CT ..1  ̨/n/ Ccn, where  ̨ is a constant in the range 0 <  ̨ < 1  and c > 0 is also a constant.

## 4.5-1

Use the master method to give tight asymptotic bounds for the following recurrences.

### a. T(n) = 2T(n/4) + 1

a = 2, b = 4, f(n) = 1, n<sup>log<sub>4</sub>2</sup> = n<sup>1/2</sup> = &Theta;(n<sup>1/2</sup>)

f(n) = O(n<sup>log<sub>4</sub>2 - &eta;</sup>) (&eta; = 1/2)

T(n) = &Theta;(n<sup>1/2</sup>)

### b. T(n) = 2T(n/4) + √n

a = 2, b = 4, f(n) = √n, n<sup>log<sub>4</sub>2</sup> = n<sup>1/2</sup> = &Theta;(n<sup>1/2</sup>)

T(n) = &Theta;(n<sup>1/2</sup>lgn)

### c. T (n) = 2T(n/4) + n

a = 2, b = 4, f(n) = n, n<sup>log<sub>4</sub>2</sup> = n<sup>1/2</sup> = &Theta;(n<sup>1/2</sup>)

f(n) = &Omega;(n<sup>1/2 + &eta;</sup>) (&eta; = 1/2)

T(n) = &Theta;(n)

### d. T(n) = 2T(n/4) + n<sup>2</sup>

a = 2, b = 4, f(n) = n<sup>2</sup>, n<sup>log<sub>4</sub>2</sup> = n<sup>1/2</sup> = &Theta;(n<sup>1/2</sup>)

f(n) = &Omega;(n<sup>1/2 + &eta;</sup>) (&eta; = 3/2)

T(n) = &Theta;(n<sup>2</sup>)

## 4.5-2

Professor Caesar wishes to develop a matrix-multiplication algorithm that is asymptotically faster than Strassen’s algorithm. His algorithm will use the divide-and-conquer method, dividing each matrix into pieces of size n/4 × n/4, and the divide and combine steps together will take &Theta;(n<sup>2</sup>) time. He needs to determine how many subproblems his algorithm has to create in order to beat Strassen’s algorithm. If his algorithm creates a subproblems, then the recurrence for the running time T(n) becomes T(n) =  aT(n/4) + &Theta;(n<sup>2</sup>). What is the largest integer value of a for which Professor Caesar’s algorithm would be asymptotically faster than Strassen’s algorithm?

b = 4, f(n) = n<sup>2</sup>, &Theta;(n<sup>log<sub>4</sub>a</sup>)

* log<sub>4</sub>a &geq; 2
  * a &geq; 16

f(n) = O(n<sup>log<sub>4</sub>a</sup> - &eta;) (&eta; > 0)

T(n) = &Theta;(n<sup>log<sub>4</sub>a</sup>) < &Theta;(n<sup>lg 7</sup>)

log<sub>4</sub>a < lg 7

lg a/2 < lg 7

lg a < 2(lg 7)

a < 49

largest a = 48

## 4.5-3

Use the master method to show that the solution to the binary-search recurrence T(n) = T(n/2) + &Theta;(1) is T(n) = &Theta;(lg n). (See Exercise 2.3-5 for a description of binary search.)

a = 1, b = 2, f(n) = &Theta;(1), n<sup>log<sub>2</sub>1</sup> = 1 = &Theta;(1)

T(n) = (lg n)

## 4.5-4

Can the master method be applied to the recurrence T(n) =  4T(n/2) + n<sup>2</sup>lg n? Why or why not? Give an asymptotic upper bound for this recurrence.

a = 4, b = 2, f(n) = n<sup>2</sup>lg n, n<sup>log<sub>2</sub>4</sup> = n<sup>2</sup> = &Theta;(n<sup>2</sup>)

f(n) ≠ O(n<sup>2 - &eta;</sup>) ≠ &Omega;O(n<sup>2 + &eta;</sup>)

assumption: T(n) ≤ cn<sup>2</sup>lg<sup>2</sup>n

## 4.5-5 ★

Consider the regularity condition af(n/b) &leq; cf(n) for some constant c < 1, which is part of case 3 of the master theorem. Give an example of constants a &geq; 1 and b > 1 and a function f(n) that satisfies all the conditions in case 3 of the master theorem except the regularity condition.

a = 1, b = 2, f(n) = n(2 - cos n)

(n/2)(2 - cos (n/2)) < cn
(1 - cos(n/2))/2 < c
1 - cos(n/2)/2 &leq; c

min cos(n/2) = -1, c &geq; 3/2, but c < 1