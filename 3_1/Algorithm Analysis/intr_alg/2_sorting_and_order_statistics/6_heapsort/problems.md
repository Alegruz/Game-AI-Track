# Problems

## 6-1 Building a heap using insertion
We can build a heap by repeatedly calling MAX-HEAP-INSERT to insert the elements into the heap. Consider the following variation on the `BUILD-MAX-HEAP` procedure:

### `BUILD-MAX-HEAP'(A)`

```
1	A.heap-size = 1
2	for i = 2 to A.length
3		MAX-HEAP-INSERT(A, A[i])
```

### a

Do the procedures `BUILD-MAX-HEAP` and `BUILD-MAX-HEAP'` always create the same heap when run on the same input array? Prove that they do, or provide a counterexample.

A = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 }

* 16
	* 14
		* 8
			* 2
			* 4
		* 7
			* 1
	* 10
		* 9
		* 3

1. 4
2. 4
	* 1
3. 4
	* 1
	* 3
4. 4
	* 1
		* 2
	* 3
5. 4
	* 1
		* 2
		* 16
	* 3
6. 16
	* 4
		* 2
		* 1
	* 3
7. 16
	* 4
		* 2
		* 1
	* 3
		* 9
8. 16
	* 4
		* 2
		* 1
	* 9
		* 3
9. 16
	* 4
		* 2
		* 1
	* 9
		* 3
		* 10
10. 16
	* 4
		* 2
		* 1
	* 10
		* 3
		* 9
11. 16
	* 4
		* 2
			* 14
		* 1
	* 10
		* 3
		* 9
12. 16
	* 14
		* 4
			* 2
		* 1
	* 10
		* 3
		* 9
13. 16
	* 14
		* 4
			* 2
			* 8
		* 1
	* 10
		* 3
		* 9
14. 16
	* 14
		* 8
			* 2
			* 4
		* 1
	* 10
		* 3
		* 9
15. 16
	* 14
		* 8
			* 2
			* 4
		* 1
			* 7
	* 10
		* 3
		* 9
16. 16
	* 14
		* 8
			* 2
			* 4
		* 7
			* 1
	* 10
		* 3
		* 9

index of and 3 and 9 differs.

### b

Show that in the worst case, `BUILD-MAX-HEAP'` requires &Theta;(n lg n) time to build an n-element heap.

Worst case would be an input array of increasing order.

For every element, (n) MAX-HEAP-INSERT performs to bubble up the input to the top, which takes O(lg n), but &Theta;(lg n) when worst-case.

Thus, &Theta;(n lg n)

## 6-2 Analysis of d -ary heaps

A ***d -ary heap*** is like a binary heap, but (with one possible exception) non-leaf nodes have d children instead of 2 children.

### a

How would you represent a d -ary heap in an array?

The same as binary heap.

Given index i,

PARENT(i) = ⌊i/d⌋
CHILDREN(i) = di..(di + d - 1)

## b

What is the height of a d -ary heap of n elements in terms of n and d?

⌊log<sub>d</sub>n⌋

### c

Give an efficient implementation of `EXTRACT-MAX` in a d -ary max-heap. Analyze its running time in terms of d and n.

```
1	if A.heap-size < 1
2		error "heap underflow"
3	max = A[1]
4	A[1] = A[A.heap-size]
5	A.heap-size = A.heap-size - 1
6	MAX-HEAPIFY(A, 1)
7	return max
```

`MAX-HEAPIFY` will take O(d log<sub>d</sub>n), thus `EXTRACT-MAX` will take O(d log<sub>d</sub>n)

### d

Give an efficient implementation of `INSERT` in a d -ary max-heap. Analyze its running time in terms of d and n.

```
1	A.heap-size = A.heap-size + 1
2	A[A.heap-size] = -∞
3	HEAP-INCREASE-KEY(A, A.heap-size, key)
```

`HEAP-INCREASE-KEY` will take O(log<sub>d</sub>n), thus `INSERT` will take O(log<sub>d</sub>n)

### e

Give an efficient implementation of INCREASE-KEY(A, i, k), which flags an error if k < A[i], but otherwise sets A[i] = k and then updates the d -ary max-heap structure appropriately. Analyze its running time in terms of d and n.

```
1	if k < A[i]
2		error "new key is smaller than current key"
3	A[i] = k
4	while i > 1 and A[PARENT(i)] < A[i]
5		exchange A[i] with A[PARENT(i)]
6		i = PARENT(i)
```

the length of the route between A[i] and the last parent it will exchange would be proportional to log<sub>d</sub>n, thus O(log<sub>d</sub>n)

## 6-3 Young tableaus

An m × n ***Young tableau*** is an m × n matrix such that the entries of each row are in sorted order from left to right and the entries of each column are in sorted order from top to bottom. Some of the entries of a Young tableau may be ∞, which we treat as nonexistent elements. Thus, a Young tableau can be used to hold r ≤ mn finite numbers.

### a

Draw a 4 × 4 Young tableau containing the elements {9, 16, 3, 2, 4, 8, 5, 14, 12}.

|1|2|3|4|
|---|---|---|---|
|2|3|8|14|
|4|5|9|16|
|12|∞|∞|∞|
|∞|∞|∞|∞|

### b

Argue that an m × n Young tableau Y is empty if Y[1, 1] = ∞. Argue that Y is full (contains mn elements) if Y[m, n] < 1.

if A[1, 1] = ∞, then for all i > 1 and j > 1, A[i, j] > A[1, 1]. this means that the rest also should be ∞, which indicates empty cells.

if A[m, n] < ∞, then for all i < m and j < n, A[i, j] < A[m, n] < ∞, thus they all have some value, making the tableau full.

### c

Give an algorithm to implement EXTRACT-MIN on a nonempty m × n Young tableau that runs in O(m + n) time. Your algorithm should use a recursive subroutine that solves an m × n problem by recursively solving either an (m - 1) × n or an m × (n - 1) subproblem. (Hint: Think about MAX-HEAPIFY.) Define T(p), where p = m + n, to be the maximum running time of EXTRACT-MIN on any m × n Young tableau. Give and solve a recurrence for T(p) that yields the O(m + n) time bound.

```
1	result = A[1, 1]
2	A[1, 1] = ∞
3	REORDER(A, 1, 1)
```

#### `REORDER(A, i, j)`

```
1	if i + 1 ≤ A.width
2		right = A[i + 1, j]
3	else
4		right = ∞
5	if j + 1 ≤ A.length
6		bottom = A[i, j + 1]
7	else
8		bottom = ∞
9	if right < bottom
10		exchange A[i, j] and right
11		REORDER(A, i + 1, j)
12	else
13		exchange A[i, j] and bottom
14		REORDER(A, i, j + 1)
```

T(p) = O(1) + T(p - 1)

T(2) = O(1) + T(1)
T(3) = O(1) + T(2)
&hellip;
T(p) = O(1) + T(p - 1)

T(p) = (p - 1)O(1) + T(1) = pO(1) = O(p)

### d

Show how to insert a new element into a nonfull m × n Young tableau in O(m + n) time.

reverse strategy of c, start from the bottom-right.

### e

Using no other sorting method as a subroutine, show how to use an n × n Young tableau to sort n<sup>2</sup> numbers in O(n<sup>3</sup>) time.

A[1, 1] is always the smallest value, thus extracting it n × n times will give sorted array.

extracting is O(n), thus total running time would be O(n<sup>3</sup>)

### f

Give an O(m + n)-time algorithm to determine whether a given number is stored in a given m × n Young tableau.

#### `CONTAINS(A, i, j, m, n, number)

```
x = i
y = n

while x ≤ m and j ≤ y
	if A[i, j] == number
		return true
	else if A[i, j] > number
		y = y - 1
	else
		x = x - 1
```

O(m + n)