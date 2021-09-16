# Exercises

## 6.1-1

What are the minimum and maximum numbers of elements in a heap of height h?

maximum: &Sigma;<sub>i=0</sub><sup>h</sup>2<sup>i</sup> = 2<sup>h + 1</sup> - 1
minimum: &Sigma;<sub>i=0</sub><sup>h - 1</sup>2<sup>i</sup> + 1= 2<sup>h</sup> - 1 + 1 = 2<sup>h</sup>

## 6.1-2

Show that an n-element heap has height ⌊lg n⌋.

this is equivalent to find the power of next smallest power of 2.

for example, if n is 6, next smallest power of 2 is 8, and its power is 3. thus the height is 2.

thus, given number n, put next smallest power of 2 as 2<sup>h</sup>

then, 2<sup>lg n</sup> &leq, 2<sup>h</sup>.

Thus, height h is ⌊lg n⌋

## 6.1-3

Show that in any subtree of a max-heap, the root of the subtree contains the largest value occurring anywhere in that subtree.

By the max-heap properties, children are always less or equal to their parent. Thus, any member in a given subtree cannot surpass their root, making it the largest value.

## 6.1-4

Where in a max-heap might the smallest element reside, assuming that all elements are distinct?

In the leaves.

## 6.1-5

Is an array that is in sorted order a min-heap?

Yes.

for example, given 1 4 6 7, this can be a min-heap.

however, given 1 4 7 5, this is a min-heap, but not a sorted order, thus vice versa is not possible.

## 6.1-6

Is the array with values <23, 17, 14, 6, 13, 10, 1, 5, 7, 12> a max-heap?

No.

* 23
	* 17
		* 6
			* 5
			* 7 -> 7 can't be a child of 6
		* 13
			* 12
	* 14
		* 10
		* 1


## 6.1-7

Show that, with the array representation for storing an n-element heap, the leaves are the nodes indexed by ⌊n/2⌋ + 1, ⌊n/2⌋ + 2,&hellip, , n.

the area between the leftmost child and rightmost child is the area of the leaves.

index of the rightmost child is trivially n.

all the nodes indexed by ⌊n/2⌋ + 1, ⌊n/2⌋ + 2,&hellip; , n has no children. thus, they are leaves

## 6.2-1

Using Figure 6.2 as a model, illustrate the operation of MAX-HEAPIFY(A, 3) on the array A = <27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0>.

1. 27
	* 17
		* 16
			* 5
			* 7
		* 13
			* 12
			* 4
	* **3**
		* 10
			* 8
			* 9
		* 1
2. 27
	* 17
		* 16
			* 5
			* 7
		* 13
			* 12
			* 4
	* 10
		* **3**
			* 8
			* 9
		* 1
2. 27
	* 17
		* 16
			* 5
			* 7
		* 13
			* 12
			* 4
	* 10
		* 9
			* 8
			* **3**
		* 1

## 6.2-2

Starting with the procedure MAX-HEAPIFY, write pseudocode for the procedure MIN-HEAPIFY(A, i), which performs the corresponding manipulation on a min-heap. How does the running time of MIN-HEAPIFY compare to that of MAX-HEAPIFY?

```
1	left = LEFT(i)
2	right = RIGHT(i)
3	if left ≤ A.heap-size and A[left] < A[i]
4		smallest = left
5	else	smallest = left
6	if right ≤ A.heap-size and A[right] < A[largest]
7		smallest = right
8	if smallest ≠ i
9		exchange A[i] with A[smallest]
10		MIN-HEAPIFY(A.smallest)
```

Running time is the same as MAX-HEAPIFY as O(lg n)

## 6.2-3

What is the effect of calling MAX-HEAPIFY(A, i) when the element A[i] is larger than its children?

nothing will happen.

## 6.2-4

What is the effect of calling MAX-HEAPIFY(A, i) for i > A.heap-size/2?

nothing. the nodes are leaves.

## 6.2-5

The code for MAX-HEAPIFY is quite efficient in terms of constant factors, except possibly for the recursive call in line 10, which might cause some compilers to produce inefficient code. Write an efficient MAX-HEAPIFY that uses an iterative control construct (a loop) instead of recursion.

&leq;

```
1   while (1 ≤ i ≤ A.length)
2		left = LEFT(i)
3		right = RIGHT(i)
4		if left ≤ A.heap-size and A[left] > A[i]
5			largest = left
6		else	largest = left
7		if right ≤ A.heap-size and A[right] > A[largest]
8			largest = right
9		if largest ≠ i
10			exchange A[i] with A[largest]
11			i = largest
12		else break
```

## 6.2-6

Show that the worst-case running time of MAX-HEAPIFY on a heap of size n is &Omega;(lg n). (Hint: For a heap with n nodes, give node values that cause MAX-HEAPIFY to be called recursively at every node on a simple path from the root down to a leaf.)

worst case is when the swap occurs at every level, thus because the height is ⌊lg n⌋, &Omega;(lg n).

## 6.3-1

Using Figure 6.3 as a model, illustrate the operation of BUILD-MAX-HEAP on the array A = <5, 3, 17, 10, 84, 19, 6, 22, 9>.

1. 5
	* 3
		* **10**
			* 22
			* 9
		* 84
	* 17
		* 19
		* 6
2. 5
	* 3
		* *22*
			* **10**
			* 9
		* 84
	* 17
		* 19
		* 6
3. 5
	* 3
		* 22
			* 10
			* 9
		* 84
	* **17**
		* 19
		* 6
4. 5
	* 3
		* 22
			* 10
			* 9
		* 84
	* *19*
		* **17**
		* 6
5. 5
	* **3**
		* 22
			* 10
			* 9
		* 84
	* 19
		* 17
		* 6
6. 5
	* *84*
		* 22
			* 10
			* 9
		* **3**
	* 19
		* 17
		* 6
6. **5**
	* 84
		* 22
			* 10
			* 9
		* 3
	* 19
		* 17
		* 6
7. *84*
	* **5**
		* 22
			* 10
			* 9
		* 3
	* 19
		* 17
		* 6
8. 84
	* *22*
		* **5**
			* 10
			* 9
		* 3
	* 19
		* 17
		* 6
9. 84
	* 22
		* *10*
			* **5**
			* 9
		* 3
	* 19
		* 17
		* 6

## 6.3-2

Why do we want the loop index i in line 2 of BUILD-MAX-HEAP to decrease from ⌊A.length/2⌋ to 1 rather than increase from 1 to ⌊A.length/2⌋?

line 3 only deals with current situation, thus if there were grandchildren larger than the root, but the children follows the property, then the max-heap property would be violated. Thus, we need to call line 3 from the lower level first.

## 6.3-3

Show that there are at most ⌈n/2<sup>h + 1</sup>⌉ nodes of height h in any n-element heap.

there are ⌈n/2⌉ number of leaves in a heap array, thus there are ⌈n/2<sup>2</sup>⌉ nodes in the higher level.

Thus in a height h, there are at most ⌈n/2<sup>h + 1</sup>⌉ nodes.

## 6.4-1

Using Figure 6.4 as a model, illustrate the operation of HEAPSORT on the array A = <5, 13, 2, 25, 7, 17, 20, 8, 4>.

1. 5
	* 13
		* 25
			* 8
			* 4
		* 7
	* 2
		* 17
		* 20
2. 25
	* 13
		* 8
			* 5
			* 4
		* 7
	* 20
		* 17
		* 2
3. 20
	* 13
		* 8
			* 5
			* 4
		* 7
	* 17
		* 2
	* (25)
4. 17
	* 13
		* 8
			* 5
			* 4
		* 7
	* 2
	* (20, 25)
5. 13
	* 8
		* 5
			* 4
		* 7
	* 2
	* (17, 20, 25)
6. 8
	* 7
		* 5
			* 4
	* 2
	* (13, 17, 20, 25)
7. 7
	* 5
		* 4
	* 2
	* (8, 13, 17, 20, 25)
8. 5
	* 4
	* 2
	* (7, 8, 13, 17, 20, 25)
9. 4
	* 2
	* (5, 7, 8, 13, 17, 20, 25)
10. 2
	* (4, 5, 7, 8, 13, 17, 20, 25)
11. (2, 4, 5, 7, 8, 13, 17, 20, 25)

## 6.4-2

Argue the correctness of HEAPSORT using the following loop invariant:

At the start of each iteration of the for loop of lines 2–5, the subarray A[1..i] is a max-heap containing the i smallest elements of A[1..n], and the subarray A[i + 1..n] contains the n - i largest elements of A[1..n], sorted.

* Initialization
	* i = A.length. Subarray A[1..i] is a max-heap, and it contains the i smallest elements of A[1..A.length].
* Maintenance
	* for each iteration, Subarray A[1..i] is a max-heap, and it contains the i smallest elements of A[1..A.length], and the subarray A[i + 1..n] equals to the part where exchange occured, thus contains the n - i largest elements of A[1..A.length] in a sorted manner.
* Termination
	* i = 1. SubArray A[1..1] is trivially a max-heap, and contains the smallest element of A[1..n], and the subarray A[2..n] is contains the rest of the elements of A[1..n] in a sorted manner.

## 6.4-3

What is the running time of HEAPSORT on an array A of length n that is already
sorted in increasing order? What about decreasing order?

O(n lg n) because BUILD-MAX-HEAP reorders the array.

if decreasing order, BUILD-MAX-HEAP does nothing, thus only MAX-HEAPIFY will occur for linear times, and MAX-HEAPIFY takes O
(lg n), thus takes total O(n lg n).

## 6.4-4

Show that the worst-case running time of HEAPSORT is &Omega;(n lg n).

The worst case would be the first case of 6.4-3 where the input array is already sorted.

## 6.4-5 ★

Show that when all elements are distinct, the best-case running time of HEAPSORT is &Omega;(n lg n).

according to the paper, The Analysis of Heapsort by Schaffer and Sedgewick,

1. Heapsort requires that at least (1/2)n lg n - O(n) data moves for any heap composed of distinct keys

Thus, (1/2)n lg n - O(n) &leq; T(n), T(n) = &Omega;(n lg n)

## 6.5-1

Illustrate the operation of HEAP-EXTRACT-MAX on the heap A = <15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1>.

1. **15**
	* 13
		* 5
			* 4
			* 0
		* 12
			* 6
			* 2
	* 9
		* 8
			* 1
		* 7
2. 1
	* 13
		* 5
			* 4
			* 0
		* 12
			* 6
			* 2
	* 9
		* 8
		* 7
	* (15)

## 6.5-2

Illustrate the operation of MAX-HEAP-INSERT(A, 10) on the heap A = <15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1>.

1. 15
	* 13
		* 5
			* 4
			* 0
		* 12
			* 6
			* 2
	* 9
		* 8
			* 1
		* 7
2. 15
	* 13
		* 5
			* 4
			* 0
		* 12
			* 6
			* 2
	* 9
		* 8
			* 1
			* **-∞**
		* 7
3. 15
	* 13
		* 5
			* 4
			* 0
		* 12
			* 6
			* 2
	* 9
		* 8
			* 1
			* **10**
		* 7
4. 15
	* 13
		* 5
			* 4
			* 0
		* 12
			* 6
			* 2
	* 9
		* **10**
			* 1
			* *8*
		* 7
5. 15
	* 13
		* 5
			* 4
			* 0
		* 12
			* 6
			* 2
	* **10**
		* *9*
			* 1
			* 8
		* 7

## 6.5-3

Write pseudocode for the procedures HEAP-MINIMUM, HEAP-EXTRACT-MIN, HEAP-DECREASE-KEY, and MIN-HEAP-INSERT that implement a min-priority queue with a min-heap.

### `HEAP-MINIMUM(A)`

```
1	return A[1]
```

### `HEAP-EXTRACT-MIN(A)`

```
1	if A.heap-size < 1
2		error "heap underflow"
3	min = A[1]
4	A[1] = A[A.heap-size]
5	A.heap-size = A.heap-size - 1
6	MIN-HEAPIFY(A, 1)
7	return min
```

### `HEAP-DECREASE-KEY(A, i)`

```
1	if key > A[i]
2		error "new key is larger than current key"
3	A[i] = key
4	while i > 1 and A[PARENT(i)] > A[i]
5		exchange A[i] with A[PARENT(i)]
6		i = PARENT(i)
```

### `MIN-HEAP-INSERT(A, key)`

```
1	A.heap-size = A.heap-size + 1
2	A[A.heap-size] = ∞
3	HEAP-DECREASE-KEY(A, A.heap-size, key)
```

## 6.5-4

Why do we bother setting the key of the inserted node to -∞ in line 2 of MAX-HEAP-INSERT when the next thing we do is increase its key to the desired value?

so that insertion itself follows the max-heap property, by assigning the lowest value possible to the last element of the array.

## 6.5-5

Argue the correctness of HEAP-INCREASE-KEY using the following loop invariant:

At the start of each iteration of the while loop of lines 4–6, the subarray A[1..A.heap-size] satisfies the max-heap property, except that there may be one violation: A[i] may be larger than A[PARENT(i)].

You may assume that the subarray A[1..A.heap-size] satisfies the max-heap property at the time HEAP-INCREASE-KEY is called.

* Initialization
	* Subarray A[1..A.heap-size] satisfies the max-heap property.
* Maintenance
	* At every iteration of the loop, Subarray A[1..A.heap-size] satisfies the max-heap property except A[i] and its parent.
* Termination
	* When i == 1, then the last iteration should have exchanged A[i] with A[1], which implies that A[i] is the largest value.
	* When A[PARENT(i)] &geq; A[i], this means that max-heap property has been retained.

## 6.5-6

Each exchange operation on line 5 of HEAP-INCREASE-KEY typically requires three assignments. Show how to use the idea of the inner loop of INSERTION-SORT to reduce the three assignments down to just one assignment.

```
while i > 1 and A[PARENT(i)] < key
	A[i] = A[PARENT(i)]
	i = PARENT(i)

A[i] = key
```

## 6.5-7

Show how to implement a first-in, first-out queue with a priority queue. Show how to implement a stack with a priority queue. (Queues and stacks are defined in Section 10.1.)

Queue: insert an input smaller than A[A.length]
Stack: always insert an input larger than A[1]

## 6.5-8

The operation HEAP-DELETE(A, i) deletes the item in node i from heap A. Give an implementation of HEAP-DELETE that runs in O(lg n) time for an n-element max-heap.

```
if A[i] > A[A.length]
	A[i] = A[A.length]
	A.length = A.length - 1
	MAX-HEAPIFY(A, i)
else
	HEAP-INCREASE-KEY(A, i, A[A.heap-size])
	A.heap-size = A.heap-size - 1
```

## 6.5-9

Give an O(n lg k)-time algorithm to merge k sorted lists into one sorted list, where n is the total number of elements in all the input lists. (Hint: Use a min-heap for k-way merging.)

Insert each element into a n-sized min-heap to merge. (insertion lg k, n times)

After merging, extract the smallest element to construct the sorted array. (extraction lg k, n times)

O(n lg k)