# Problems

## 2-1 Insertion sort on small arrays in merge sort

Although merge sort runs in &theta;(*n log*<sub>2</sub> *n*) worst-case time and insertion sort runs in &theta;(n<sup>2</sup>) worst-case time, the constant factors in insertion sort can make it faster in practice for small problem sizes on many machines. Thus, it makes sense to
coarsen the leaves of the recursion by using insertion sort within merge sort when subproblems become sufficiently small. Consider a modification to merge sort in which *n* / *k* sublists of length k are sorted using insertion sort and then merged using the standard merging mechanism, where *k* is a value to be determined.

a. Show that insertion sort can sort the *n* / *k* sublists, each of length *k*, in &theta;(*nk*) worst-case time.
b. Show how to merge the sublists in &theta;(*n log*<sub>2</sub> (*n*/*k*)) worst-case time
c. Given that the modified algorithm runs in &theta;(*nk* + *n log*<sub>2</sub> (*n*/*k*)) worst-case time, what is the largest value of *k* as a function of *n* for which the modified algorithm has the same running time as standard merge sort, in terms of &theta;-notation?
d. How should we choose *k* in practice?

## 2-2 Correctness of bubblesort

Bubblesort is a popular, but inefficient, sorting algorithm. It works by repeatedly swapping adjacent elements that are out of order.

### BUBBLESORT(*A*)

```
for i = 1 to A.length - 1
	for j = A.length downto i + 1
		if A[j] < A[j - 1]
			exchange A[j] with A[j - 1]
```

a. Let *A*' denote the output of BUBBLESORT(*A*). To prove that BUBBLESORT is correct, we need to prove that it terminates and that<br> *A*'[1] &leq; *A*'[2] &leg; &hellip; &leq; *A*'[*n*], (2.3)<br> where *n* = *A.length*. In order to show that BUBBLESORT actually sorts, what else do we need to prove?

The next two parts will prove inequality (2.3).

b. State precisely a loop invariant for the for loop in lines 2–4, and prove that this loop invariant holds. Your proof should use the structure of the loop invariant proof presented in this chapter.
c. Using the termination condition of the loop invariant proved in part (b), state a loop invariant for the for loop in lines 1–4 that will allow you to prove inequality (2.3). Your proof should use the structure of the loop invariant proof presented in this chapter.
d. What is the worst-case running time of bubblesort? How does it compare to the running time of insertion sort?

## 2-3 Correctness of Horner’s rule
 
The following code fragment implements Horner’s rule for evaluating a polynomial

*P*(*x*) = &Sigma;X<sub>*k* = 0</sub><sup>*n*</sup>*a<sub>k</sub> x<sup>k</sup>*<br>
=  *a*<sub>0</sub>0 + *x*(*a*<sub>1</sub> + *x*(*a*<sub>2</sub> + &hellip; * *x*(*a*<sub>*n* - 1</sub> + *xa<sub>n</sub>*) &hellip;)).

given the coefficients *a*<sub>0</sub>, *a*<sub>1</sub>, &hellip; *a<sub>n</sub>* and *a* value for *x*:

<code>
y = 0<br>
for i = n downto 0<br>
&nbsp;&nbsp;&nbsp;&nbsp;y = a<sub>i</sub> + x &sdot; y
</code>

a. In terms of &theta;-notation, what is the running time of this code fragment for Horner’s rule?
b. Write pseudocode to implement the naive polynomial-evaluation algorithm that computes each term of the polynomial from scratch. What is the running time
of this algorithm? How does it compare to Horner’s rule?
c. Consider the following loop invariant:<br>At the start of each iteration of the `for` loop of lines 2–3,<br>*y* = &Sigma;<sub>*k*=0</sub><sup>*n*-(*i*+1)</sup>*a*<sub>*k*+*i*+1</sub>*x<sup>k*</sup>.<br>Interpret a summation with no terms as equaling 0. Following the structure of the loop invariant proof presented in this chapter, use this loop invariant to show that, at termination, *y* = &Sigma;<sub>*k*=0</sub><sup>*n*</sup>*a*<sub>*k*</sub>*x<sup>k*</sup>
d. Conclude by arguing that the given code fragment correctly evaluates a polynomial characterized by the coefficients *a*<sub>0</sub>, *a*<sub>1</sub>, &hellip, *a*<sub>*n*</sub>.

## 2-4 Inversions

Let *A*[1&hellip;*n*] be an array of n distinct numbers. If *i* < *j* and *A*[*i*] > *A*[*j*], then the pair (*i*, *j*) is called an ***inversion*** of *A*.

a. List the five inversions of the array &lt;2, 3, 8, 6, 1>.
b. What array with elements from the set {1, 2, &hellip;, *n*} has the most inversions? How many does it have?
c. What is the relationship between the running time of insertion sort and the number of inversions in the input array? Justify your answer.
d. Give an algorithm that determines the number of inversions in any permutation on *n* elements in &theta;(*n log*<sub>2</sub> *n*) worst-case time. (Hint: Modify merge sorts.)
