# Exercises

## 7.1-1

Using figure below as a model, illustrate the operation of PARTITION on the array A = <13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11>.

![7_1](https://media.vlpt.us/images/alegruz/post/15327d94-f28e-47bb-9bf1-8689605e6138/Screenshot%202021-09-29%20at%2010-27-40%20Introduction%20to%20Algorithms,%20Third%20Edition%20-%20Introduction_to_algorithms-3rd%20Edition%20pdf.png)

1. <table><thead><tr><th>i</th><th>p, j</th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td>13</td><td>19</td><td>9</td><td>5</td><td>12</td><td>8</td><td>7</td><td>4</td><td>21</td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
2. <table><thead><tr><th>i</th><th>p</th><th>j</th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td><strong>13</strong></td><td>19</td><td>9</td><td>5</td><td>12</td><td>8</td><td>7</td><td>4</td><td>21</td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
3. <table><thead><tr><th>i</th><th>p</th><th></th><th>j</th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td><strong>13</strong></td><td><strong>19</strong></td><td>9</td><td>5</td><td>12</td><td>8</td><td>7</td><td>4</td><td>21</td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
4. <table><thead><tr><th></th><th>p, i</th><th></th><th></th><th>j</th><th></th><th></th><th></th><th></th><th></th><th></th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><strong>19</strong></td><td><strong>13</strong></td><td>5</td><td>12</td><td>8</td><td>7</td><td>4</td><td>21</td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
5. <table><thead><tr><th></th><th>p</th><th>i</th><th></th><th></th><th>j</th><th></th><th></th><th></th><th></th><th></th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><i>5</i></td><td><strong>13</strong></td><td><strong>19</strong></td><td>12</td><td>8</td><td>7</td><td>4</td><td>21</td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
6. <table><thead><tr><th></th><th>p</th><th>i</th><th></th><th></th><th></th><th>j</th><th></th><th></th><th></th><th></th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><i>5</i></td><td><strong>13</strong></td><td><strong>19</strong></td><td><strong>12</strong></td><td>8</td><td>7</td><td>4</td><td>21</td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
7. <table><thead><tr><th></th><th>p</th><th></th><th>i</th><th></th><th></th><th></th><th>j</th><th></th><th></th><th></th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><i>5</i></td><td><i>8</i></td></td><td><strong>19</strong></td><td><strong>12</strong></td><td><strong>13</strong><td>7</td><td>4</td><td>21</td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
8. <table><thead><tr><th></th><th>p</th><th></th><th></th><th>i</th><th></th><th></th><th></th><th>j</th><th></th><th></th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><i>5</i></td><td><i>8</i></td><td><i>7</i></td><td><strong>12</strong></td><td><strong>13</strong><td><strong>19</strong></td><td>4</td><td>21</td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
9. <table><thead><tr><th></th><th>p</th><th></th><th></th><th></th><th>i</th><th></th><th></th><th></th><th>j</th><th></th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><i>5</i></td><td><i>8</i></td><td><i>7</i></td><td><i>4</i></td><td><strong>12</strong></td><td><strong>13</strong><td><strong>19</strong></td><td>21</td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
10. <table><thead><tr><th></th><th>p</th><th></th><th></th><th></th><th>i</th><th></th><th></th><th></th><th></th><th>j</th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><i>5</i></td><td><i>8</i></td><td><i>7</i></td><td><i>4</i></td><td><strong>12</strong></td><td><strong>13</strong><td><strong>19</strong></td><td><strong>21</strong></td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
11. <table><thead><tr><th></th><th>p</th><th></th><th></th><th></th><th>i</th><th></th><th></th><th></th><th>j</th><th></th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><i>5</i></td><td><i>8</i></td><td><i>7</i></td><td><i>4</i></td><td><strong>12</strong></td><td><strong>13</strong><td><strong>19</strong></td><td>21</td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
12. <table><thead><tr><th></th><th>p</th><th></th><th></th><th></th><th>i</th><th></th><th></th><th></th><th></th><th>j</th><th></th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><i>5</i></td><td><i>8</i></td><td><i>7</i></td><td><i>4</i></td><td><strong>12</strong></td><td><strong>13</strong><td><strong>19</strong></td><td><strong>21</strong></td><td>2</td><td>6</td><td>11</td></tr></tbody></table>
13. <table><thead><tr><th></th><th>p</th><th></th><th></th><th></th><th></th><th>i</th><th></th><th></th><th></th><th></th><th>j</th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><i>5</i></td><td><i>8</i></td><td><i>7</i></td><td><i>4</i></td><td><i>2</i></td><td><strong>13</strong><td><strong>19</strong></td><td><strong>21</strong></td><td><strong>12</strong></td><td>6</td><td>11</td></tr></tbody></table>
14. <table><thead><tr><th></th><th>p</th><th></th><th></th><th></th><th></th><th></th><th>i</th><th></th><th></th><th></th><th>j</th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><i>5</i></td><td><i>8</i></td><td><i>7</i></td><td><i>4</i></td><td><i>2</i></td><td><i>6</i></td><td><strong>19</strong></td><td><strong>21</strong></td><td><strong>12</strong></td><td><strong>13</strong></td><td>11</td></tr></tbody></table>
15. <table><thead><tr><th></th><th>p</th><th></th><th></th><th></th><th></th><th></th><th>i</th><th></th><th></th><th></th><th>j</th><th>r</th></tr></thead><tbody><tr><td></td><td><i>9</i></td><td><i>5</i></td><td><i>8</i></td><td><i>7</i></td><td><i>4</i></td><td><i>2</i></td><td><i>6</i></td><td><u>11</u></td><td><strong>19</strong></td><td><strong>21</strong></td><td><strong>12</strong></td><td><strong>13</strong></td></tr></tbody></table>

## 7.1-2

What value of q does `PARTITION` return when all elements in the array A[p..r] have the same value? Modify `PARTITION` so that q = ⌊(p + r)/2⌋ when all elements in the array A[p..r] have the same value.

`PARTITION` returns r.

```
1	x = A[r]
2	i = p - 1
3	equal_count = 0
4	for j = p to r - 1
5		equal_count += 1 * (A[j] == x)
6		if A[j] <= x
7			i = i + 1
8			exchange A[i] with A[j]
9	exchange A[i + 1] with A[r]
10	return (i + 1) - equal_count / 2
```

## 7.1-3

Give a brief argument that the running time of `PARTITION` on a subarray of size n is &Theta;(n).

there is a single `for` loop from p to r - 1, which is n - 1.

## 7.1-4

How would you modify `QUICKSORT` to sort into nonincreasing order?

flip the condition in line 4 of `PARTITION`

## 7.2-1

Use the substitution method to prove that the recurrence T(n) = T(n - 1) + &Theta;(n) has the solution T(n) = &Theta;(n<sup>2</sup>), as claimed at the beginning of Section 7.2.

assume T(n) &leq; c<sub>1</sub>n<sup>2</sup>

T(n) = T(n - 1) + &Theta;(n) &leq; c(n - 1)<sup>2</sup> &Theta;(n) = cn<sup>2</sup> + cn - c + &Theta; &leq; cn<sup>2</sup>

## 7.2-2

What is the running time of `QUICKSORT` when all elements of array A have the same value?

line 4 occurs every time, and the partitioning always results in n - 1 and 0 subarrays:

T(n) = T(n - 1) + &Theta;(n)

T(n) = &Theta;(n<sup>2</sup>)

## 7.2-3

Show that the running time of `QUICKSORT` is &Theta;(n<sup>2</sup>) when the array A contains distinct elements and is sorted in decreasing order.

If elements are all sorted in decreasing order, the pivot element will always be the smallest element, thus partition takes &Theta;(n). Then we have subarrays of size n - 1 and 0:

T(n) = T(n - 1) + &Theta;(n)

T(n) = &Theta;(n<sup>2</sup>)

## 7.2-4

Banks often record transactions on an account in order of the times of the transactions, but many people like to receive their bank statements with checks listed in order by check number. People usually write checks in order by check number, and merchants usually cash them with reasonable dispatch. The problem of converting time-of-transaction ordering to check-number ordering is therefore the problem of sorting almost-sorted input. Argue that the procedure `INSERTION-SORT` would tend to beat the procedure `QUICKSORT` on this problem.

`QUICKSORT` is inefficient where arrays are already sorted, and `INSERTION-SORT` works best when arrays are already sorted.

## 7.2-5

Suppose that the splits at every level of quicksort are in the proportion 1 - &alpha; to &alpha; where 0 <  &alpha; &leq; 1/2 is a constant. Show that the minimum depth of a leaf in the recursion tree is approximately -lg n / lg &alpha; and the maximum depth is approximately -lg n / lg(1 - &alpha;) (Don’t worry about integer round-off.)

if given size is n, then it will be splitted into (1 - &alpha;)n and &alpha;n. for &alpha; < 1 - &alpha;, the minimum depth can be calculated by the power of &alpha;. if the minimum depth is d, then &alpha;<sup>d</sup>n = 1. thus, k = log<sub>a</sub>(1/n) = -lg n / lg &alpha;. maximum depth is vice versa, thus change &alpha; with (1 - &alpha;)

## 7.2-6 &#9733;

Argue that for any constant 0 < &alpha; &leq; 1/2, the probability is approximately 1 - 2&alpha; that on a random input array, `PARTITION` produces a split more balanced than 1 - &alpha; to &alpha;.

## 7.3-1

Why do we analyze the expected running time of a randomized algorithm and not its worst-case running time?

In order to see if randomized algorithms performs adequately in real-world situations.

## 7.3-2

When `RANDOMIZED-QUICKSORT` runs, how many calls are made to the random-number generator `RANDOM` in the worst case? How about in the best case? Give your answer in terms of &Theta;-notation.

&Theta;(n)

## 7.4-1

Show that in the recurrence

T(n) = max<sub>0&leq;q&leq;n-1</sub>(T(q) + T(n - q - 1)) + &Theta;(n)
T(n) = &Omega;(n<sup>2</sup>)

Assume T(n) &geq; cn<sup>2</sup> - dn.

T(n) = max<sub>0&leq;q&leq;n-1</sub>(T(q) + T(n - q - 1)) + &Theta;(n) &geq; max<sub>0&leq;q&leq;n-1</sub>(cq<sup>2</sup> - dq + c(n - q - 1)<sup>2</sup> - d(n - q - 1)) + &Theta;(n) = c max<sub>0&leq;q&leq;n-1</sub>(q<sup>2</sup> + (n - q - 1)<sup>2</sup> - d(n - 1)/c) + &Theta;(n) &geq; cn<sup>2</sup>

max is when q = 0

T(n) &geq; cn<sup>2</sup> - d(n - 1) + &Theta;(n)  &geq; cn<sup>2</sup> - dn + d &geq; cn<sup>2</sup> - dn

T(n) = &Omega;(n<sup>2</sup>)

## 7.4-2

Show that quicksort’s best-case running time is &Omega;(n lg n).

Quicksort's best-case is when partition is balanced.

T(n) = min<sub>1&leq;q&leq;n-1</sub>(T(q) + T(n - q - 1)) + &Theta;

Assume T(n) &geq; cn lg n - dn

T(n) &geq; min<sub>1&leq;q&leq;n-1</sub>(cq lg q - dq + c(n - q - 1) lg (n - q - 1) - d(n - q - 1)) + &Theta;

min when q = (n - 1) / 2

T(n) &geq; c (n - 1) lg (n - 1)/2 - 2dn + 2d,

Thus, T(n) = &Omega;(n lg n)

## 7.4-3

Show that the expression q<sup>2</sup> + (n - q - 1)<sup>2</sup> achieves a maximum over q = 0, 1, &hellip;, n - 1 when q = 0 or q = n - 1.

f(q) = q<sup>2</sup> + (n - q - 1)<sup>2</sup>
f'(q) = 2q - 2(n - q - 1) = 4q - 2n + 2

thus, f(q) decreases until q = n - 1 / 2, then increases.

Thus, maximum of the quadratic function f(q) is either 0 or n - 1.

## 7.4-4

Show that `RANDOMIZED-QUICKSORT`’s expected running time is &Omega;(n lg n).

## 7.4-5

We can improve the running time of quicksort in practice by taking advantage of the fast running time of insertion sort when its input is “nearly” sorted. Upon calling quicksort on a subarray with fewer than k elements, let it simply return without sorting the subarray. After the top-level call to quicksort returns, run insertion sort on the entire array to finish the sorting process. Argue that this sorting algorithm runs in O(nk + n lg(n/k)) expected time. How should we pick k, both in theory and in practice?

Depth would be lg n/k, thus O(n lg (n/k)), then we will perform insertion sort for the unsorted n/k arrays of size k, thus O(nk).

* c<sub>q</sub>n lg n &geq; c<sub>i</sub>nk c<sub>q</sub>n lg (n/k)
* c<sub>q</sub>n lg k &geq; c<sub>i</sub>nk
* c<sub>q</sub>lg k &geq; c<sub>i</sub>k

k should be picked not just mathematically, but also by taking closer measures and experiment.

## 7.4-6 &#9733;

Consider modifying the `PARTITION` procedure by randomly picking three elements from array A and partitioning about their median (the middle value of the three elements). Approximate the probability of getting at worst an &alpha;-to-(1 - &alpha;) split, as a function of &alpha; in the range 0 < &alpha; < 1 