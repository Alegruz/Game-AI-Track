# Exercises

## 2.1-1

Using Figure 2.2 as a model, illustrate the operation of INSERTION-SORT on the array *A* = &lt;31, 41, 59, 26, 41, 58>.

1. *31* **41** 59 26 41 58
2. 31 *41* **59** 26 41 58
3. *31 41 59* **26** 41 58 (insert in front of 31)
4. *26 31 41 59* **41** 58 (insert in front of 59)
5. *26 31 41 41 59* **58** (insert in front of 59)
6. 26 31 41 41 58 59

## 2.1-2

Rewrite the INSERTION-SORT procedure to sort into nonincreasing instead of non-decreasing order.

```
for j = 2 to A.length
	key = A[j]
	// Insert A[j] into the sorted sequence A[1..j - 1].
	i = j - 1
	while i > 0 and A[i] < key
		A[i + 1] = A[i]
		i = i - 1
	A[i + 1] = key
```

## 2.1-3

Consider the ***searching problem***:

* **Input**: A sequence of *n* numbers *A* = &lt;*a*<sub>1</sub>, *a*<sub>2</sub>, &hellip;, *a*<sub>n</sub>> and a value *v*.
* **Output**: An index *i* such that *v* = *A*[i] or the special value *NIL* if *v* does not appear in *A*.

Write pseudocode for ***linear search***, which scans through the sequence, looking for *v*. Using a loop invariant, prove that your algorithm is correct. Make sure that your loop invariant fulfills the three necessary properties.

```
for i = 1 to A.length
	if A[i] == v:
		return i

return NIL
```

* **Initialization**: when j = 1, we can tell if A[i] equals to v or not, thus loop invariant holds prior to the first iteration of the loop.
* **Maintenance**: for each iteration, we can tell if A[j] equals to v or not, and because we are running current iteration, we haven't found *v* yet.
* **Termination**: When i exceeds A.length, there are no element to check, thus the algorithm returns NIL, which yet again preserves the loop invariant. Hence the algorithm is correct.

## 2.1-4

Consider the problem of adding two n-bit binary integers, stored in two *n*-element arrays *A* and *B*. The sum of the two integers should be stored in binary form in an (*n* + 1)-element array *C*. State the problem formally and write pseudocode for adding the two integers.

```
carry = 0
for i = 1 to A.length
	if A[i] == 1 and (B[i] == 1 or carry == 1)
		carry = 1
	C[i] = (A[i] == 1) xor (B[i] == 1)
```

## 2.2-1

Express the function n<sup>3</sup> / 1000 - 100n<sup>2</sup> - 100n + 3 in terms of‚ &theta;-notation.

&theta;(*n*<sup>3</sup>)

## 2.2-2

Consider sorting n numbers stored in array *A* by first finding the smallest element of A and exchanging it with the element in *A*[1]. Then find the second smallest element of *A*, and exchange it with *A*[2]. Continue in this manner for the first *n* - 1 elements of *A*. Write pseudocode for this algorithm, which is known as ***selection sort***. What loop invariant does this algorithm maintain? Why does it need to run for only the first *n* - 1 elements, rather than for all *n* elements? Give the best-case and worst-case running times of selection sort in &theta;-notation.

### Loop variant

All three of them.

### First n - 1 elements

Because the last element remaining would automatically be the largest element of *A*.

### Best-case / Worst-case

&theta;(n<sup>2</sup>)

## 2.2-3

Consider linear search again (see Exercise 2.1-3). How many elements of the input sequence need to be checked on the average, assuming that the element being searched for is equally likely to be any element in the array? How about in the worst case? What are the average-case and worst-case running times of linear search in &theta;-notation? Justify your answers.

* average: &theta;(*n* / 2)
* worst-case: &theta;(*n*)

## 2.2-4

How can we modify almost any algorithm to have a good best-case running time?

Modify the data before performing the algorithm. Sort them firsthand for example.

## 2.3-1

Using Figure 2.4 as a model, illustrate the operation of merge sort on the array A = &lt;3, 41, 52, 26, 38, 57, 9, 49>.

1. (3) (41) (52) (26) (38) (57) (9)
2. (3 41) (26 52) (38 57) (9)
3. (3 26 41 52) (9 38 57)
4. (3 9 26 38 41 52 57)

## 2.3-2

Rewrite the MERGE procedure so that it does not use sentinels, instead stopping once either array *L* or *R* has had all its elements copied back to A and then copying the remainder of the other array back into *A*.

```
a_index = 0
b_index = 0
while a_index ≤ A.length || b_index ≤ B.length
	if A[a_index] < B[b_index]
		C[a_index + b_index] = A[a_index]
		a_index = a_index + 1
	else
		C[a_index + b_index] = B[b_index]
		b_index = b_index + 1

while a_index ≤ A.length
	C[a_index + b_index] = A[a_index]
	a_index = a_index + 1

while b_index ≤ B.length
	C[a_index + b_index] = B[b_index]
	b_index = b_index + 1
```

## 2.3-3

Use mathematical induction to show that when n is an exact power of 2, the solution of the recurrence

*T*(*n*) =

* 2 if *n* = 2
* 2*T*(*n*/2) + *n* if *n* = 2<sup>*k*</sup>, for *k* > 1

is *T*(*n*) = *n log*<sub>2</sub> *n*.

1. n = 2. T(2) = 2
2. n = 4. T(4) = 2T(2) + 4 = 4 + 4 = 8 = 4 * 2
3. n = 8. T(8) = 2T(4) + 8 = 16 + 8 = 24 = 8 * 3
4. n = 16. T(16) = 2T(8) + 16 = 48 + 16 = 64 = 16 * 5
5. n = 32. T(32) = 2T(16) + 32 = 128 + 32 = 160 = 32 * 6
6. &hellip;
7. T(n) = n * log<sub>2</sub> n

## 2.3-4

We can express insertion sort as a recursive procedure as follows. In order to sort *A*[1..n], we recursively sort *A*[1..*n* - 1] and then insert *A*[n] into the sorted array *A*[1..*n* - 1]. Write a recurrence for the running time of this recursive version of insertion sort.

```
void insertion_sort_recursive(int[] A, int size)
	if size > 1
		insertion_sort_recursive(A, A.length - 1)
	
	key = A[size]
	while i > 0 and A[i] > key
		A[i + 1] = A[i]
		i = i - 1
	A[i + 1] = key
```

## 2.3-5

Referring back to the searching problem (see Exercise 2.1-3), observe that if the sequence *A* is sorted, we can check the midpoint of the sequence against *v* and eliminate half of the sequence from further consideration. The binary search algorithm repeats this procedure, halving the size of the remaining portion of the sequence each time. Write pseudocode, either iterative or recursive, for binary
search. Argue that the worst-case running time of binary search is &theta;(*log*<sub>2</sub> *n*).

```
left_index = 0
right_index = A.length

while left_index ≤ right_index
	mid_index = (left_index + right_index) / 2

	if A[mid_index] == v
		return mid_index
	else if A[mid_index] ≤ v
		left_index = mid_index + 1
	else
		right_index = mid_index - 1

return NIL
```

We can illustrate this problem into a balanced binary tree. Worst-case running time of search in balanced binary tree for maximum depth of a balanced binary tree is &theta(*log*<sub>2</sub> *n*).

## 2.3-6

Observe that the `while` loop of lines 5–7 of the INSERTION-SORT procedure in Section 2.1 uses a linear search to scan (backward) through the sorted subarray A[1..*j* - 1]. Can we use a binary search (see Exercise 2.3-5) instead to improve the overall worst-case running time of insertion sort to &theta;(*n log*<sub>2</sub> *n*)?

Insertion sort needs to insert an item during sorting, thus worst-case running time will remain &theta;(*n*<sup>2</sup>)

## 2.3-7 *

Describe *a* &theta;(*n log*<sub>2</sub> *n*)-time algorithm that, given a set *S* of *n* integers and another integer *x*, determines whether or not there exist two elements in *S* whose sum is exactly *x*

1. sort the array
2. for every element in the array
   1. use binary search to if its counter part exists in the array
