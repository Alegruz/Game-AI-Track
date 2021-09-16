# Problems

## 3-1 Asymptotic behavior of polynomials

Let

p(n) = ∑<sub>i=0</sub><sup>d</sup>a<sub>i</sub>n<sup>i</sup>

where a<sub>d</sub> > 0 , be a degree-d polynomial in n, and let k be a constant. Use the definitions of the asymptotic notations to prove the following properties.

a. If k &geq; d , then p(n) = O(n<sup>k</sup>).
b. If k &leq; d , then p(n) = &Omega;(n<sup>k</sup>).
c. If k = d , then p(n) = &Theta;(n<sup>k</sup>).
d. If k > d , then p(n) = o(n<sup>k</sup>).
e. If k < d , then p(n) = &omega;(n<sup>k</sup>).

### a. If k &geq; d , then p(n) = O(n<sup>k</sup>)

* ∑<sub>i=0</sub><sup>d</sup>a<sub>i</sub>n<sup>i</sup> = a<sub>d</sub>n<sup>d</sup> + a<sub>d - 1</sub>n<sup>n - 1</sup> + &hellip; + a<sub>0</sub>n<sup>0</sup>
  * divide by n<sup>d</sup>
  * a<sub>d</sub> + a<sub>d - 1</sub>/n<sup>1</sup> + &hellip; + a<sub>0</sub>/n<sup>d</sup> &leq; a<sub>d</sub> + b (b &geq; a<sub>d - 1</sub>/n<sup>1</sup> + &hellip; + a<sub>0</sub>/n<sup>d</sup>)
  * let b = 1, then n<sub>0</sub> = max(da<sub>d-1</sub>, d√a<sub>d-2</sub>, &hellip;, d<sup>d</sup>√a<sub>0</sub>)
  * p(n) = O(n<sup>d</sup>) = O(n<sup>k</sup>)

### b. If k &leq; d , then p(n) = &Omega;(n<sup>k</sup>)

* ∑<sub>i=0</sub><sup>d</sup>a<sub>i</sub>n<sup>i</sup> = a<sub>d</sub>n<sup>d</sup> + a<sub>d - 1</sub>n<sup>n - 1</sup> + &hellip; + a<sub>0</sub>n<sup>0</sup>
  * lim<sub>n→∞</sub>((a<sub>d</sub>n<sup>d</sup> + a<sub>d - 1</sub>n<sup>n - 1</sup> + &hellip; + a<sub>0</sub>n<sup>0</sup>)/cn<sup>k</sup>)
    * lim<sub>n→∞</sub>((a<sub>d</sub>/c)n<sup>d - k</sup> + (a<sub>d - 1</sub>/c)n<sup>d - 1 - k</sup> + &hellip; + (a<sub>k</sub>/c) + (a<sub>k - 1</sub>/c)/n + &hellip; + (a<sub>0</sub>/c)/n<sup>k</sup>)
      * ∞ if d > k, a<sub>d</sub>/c if d = k
    * thus, p(n) &geq; cn<sup>k</sup> for (n &geq; n<sub>0</sub>)

### c. If k = d , then p(n) = &Theta;(n<sup>k</sup>)

* if k = d, p(n) = O(n<sup>k</sup>) and p(n) = &Omega;(n<sup>k</sup>)

### d. If k > d , then p(n) = o(n<sup>k</sup>)

* ∑<sub>i=0</sub><sup>d</sup>a<sub>i</sub>n<sup>i</sup> = a<sub>d</sub>n<sup>d</sup> + a<sub>d - 1</sub>n<sup>n - 1</sup> + &hellip; + a<sub>0</sub>n<sup>0</sup>
  * lim<sub>n→∞</sub>((a<sub>d</sub>n<sup>d</sup> + a<sub>d - 1</sub>n<sup>n - 1</sup> + &hellip; + a<sub>0</sub>n<sup>0</sup>)/cn<sup>k</sup>)
    * lim<sub>n→∞</sub>((a<sub>d</sub>/c)/n<sup>k - d</sup> + (a<sub>d - 1</sub>/c)/n<sup>k - (d - 1)</sup> + &hellip; + (a<sub>0</sub>/c)/n<sup>k</sup>) = 0
    * thus, p(n) < cn<sup>k</sup> for (n &geq; n<sub>0</sub>)

### e. If k < d , then p(n) = &omega;(n<sup>k</sup>)

* ∑<sub>i=0</sub><sup>d</sup>a<sub>i</sub>n<sup>i</sup> = a<sub>d</sub>n<sup>d</sup> + a<sub>d - 1</sub>n<sup>n - 1</sup> + &hellip; + a<sub>0</sub>n<sup>0</sup>
  * lim<sub>n→∞</sub>((a<sub>d</sub>n<sup>d</sup> + a<sub>d - 1</sub>n<sup>n - 1</sup> + &hellip; + a<sub>0</sub>n<sup>0</sup>)/cn<sup>k</sup>)
    * lim<sub>n→∞</sub>((a<sub>d</sub>/c)n<sup>d - k</sup> + (a<sub>d - 1</sub>/c)n<sup>d - 1 - k</sup> + &hellip; + (a<sub>k</sub>/c) + (a<sub>k - 1</sub>/c)/n + &hellip; + (a<sub>0</sub>/c)/n<sup>k</sup>) = ∞
    * thus, p(n) &geq; cn<sup>k</sup> for (n &geq; n<sub>0</sub>)

## 3-2 Relative asymptotic growths

Indicate, for each pair of expressions .A; B/ in the table below, whether A is O, o, &Omega;, &omega;, or &Theta; of B. Assume that k &geq; 1, &eta; > 0 , and c > 1 are constants. Your answer should be in the form of the table with “yes” or “no” written in each box.

|A|B|O|o|&Omega;|&omega;|&Theta;|
|---|---|---|---|---|---|---|
|log<sub>2</sub><sup>k</sup>n|n<sup>&eta;</sup>|yes|yes|no|no|no|
|n<sup>k</sup>|c<sup>n</sup>|yes|yes|no|no|no|
|√n|n<sup>sin n</sup>|no|no|no|no|no|
|2<sup>n</sup>|2<sup>n/2</sup>|no|no|yes|yes|no|
|n<sup>log<sub>2</sub>c</sup>|c<sup>log<sub>2</sub>n</sup>|yes|no|yes|no|yes|
|log<sub>2</sub>(n!)|log<sub>2</sub>(n<sup>n</sup>)|yes|no|yes|no|yes|

## 3-3 Ordering by asymptotic growth rates

a. Rank the following functions by order of growth; that is, find an arrangement g<sub>1</sub>, &hellip, g<sub>30</sub> of the functions satisfying g<sub>1</sub> = &Omega;(g<sub>2</sub>), &hellip;, g<sub>29</sub> = &Omega;(g<sub>30</sub>). Partition your list into equivalence classes such that functions f(n) and g(n) are in the same class if and only if f(n) = &Theta;(g(n)).

1. 2<sup>2<sup>n + 1</sup></sup>
2. 2<sup>2<sup>n</sup></sup>
3. (n + 1)!
4. n!
5. e<sup>n</sup>
6. n ⋅ 2<sup>n</sup>
7. 2<sup>n</sup>
8. (3/2)<sup>n</sup>
9. n<sup>lg lg n</sup>
10. (lg n)<sup>lg n</sup>
11. (lg n)!
12. n<sup>3</sup>
13. 4<sup>lg n</sup>
14. n<sup>2</sup>
15. lg(n!)
16. n lg n
17. 2<sup>lg n</sup>
18. n
19. (√2)<sup>lg n</sup>
20. 2<sup>√(2lg n)</sup>
21. lg<sup>2</sup> n
22. ln n
23. √lg n
24. ln ln n
25. 2<sup>lg<sup>*</sup>n</sup>
26. lg<sup>*</sup>(lg n)
27. lg<sup>*</sup> n
28. lg(lg<sup>*</sup> n)
29. n<sup>1/lg n</sup>
30. 1

b. Give an example of a single nonnegative function f(n) such that for all functions g<sub>i</sub>(n) in part (a), f(n) is neither O(g<sub>i</sub>(n)) nor &Omega;(g<sub>i</sub>(n)).

f(n) = 2<sup>n<sup>sin n</sup></sup>

## 3-4 Asymptotic notation properties

Let f(n) and g(n) be asymptotically positive functions. Prove or disprove each of the following conjectures.

1. f(n) = O(g(n)) implies g(n) = O(f(n)).
   * disprove. f(n) = n, g(n) = n<sup>2</sup>
2. f(n) + g(n) = &Theta;min(f(n), g(n))).
   * disprove. f(n) = n, g(n) = n<sup>2</sup>
3. f(n) = O(g(n)) implies lg(f(n)) = O(lg(g(n))), where lg(g(n)) &geq; 1 and f(n) &geq; 1 for all sufficiently large n.
   * prove. f(n) &geq; 1 -> 0 &leq; lg(f(n)) &leq; lg(cg(n)) = lg c + lg g(n)
     * lg f(n) &leq; d lg g(n)
     * d = (lg c + lg g(n)) / lg g(n) = lg c / lg g(n) + 1 &leq; lg c + 1
4. f(n) = O(g(n)) implies 2<sup>f(n)</sup> = O(2<sup>g(n)</sup>).
   * disprove. f(n) = 2n, 4<sup>n</sup> ≠ O(2<sup>n</sup>)
5. f(n) = O((f(n))<sup>2</sup>).
   * prove. 0 &leq; f(n) &geq; c(f(n))<sup>2</sup>
6. f(n) = O(g(n)) implies g(n) = &Omega;(f(n)).
   * prove. 0 &leq; f(n) &leq; cg(n)
     * 0 &leq; (1/c)f(n) &leq; g(n)
7. f(n) = &Theta;(f(n/2)).
   * disprove. f(n) = 2<sup>n</sup> 
8. f(n) + o(f(n)) = &Theta;(f(n)).
   * prove. 0 &leq; o(f(n)) < cf(n)
     * 0 &leq; f(n) &leq; f(n) + o(g(f(n))) &leq; f(n) + c(f(n))

## 3-5 Variations on O and &Omega;

Some authors define &Omega; in a slightly different way than we do; let’s use &Omega;<sup>∞</sup> (read
“omega infinity”) for this alternative definition. We say that f(n) = &Omega;<sup>∞</sup>(g(n)) if there exists a positive constant c such that f(n) &geq; cg(n) &geq; 0 for infinitely many integers n.

1. Show that for any two functions f(n) and g(n) that are asymptotically nonnegative, either f(n) = O(g(n)) or f(n) = &Omega;<sup>∞</sup>(g(n)) or both, whereas this is not true if we use &Omega; in place of &Omega;<sup>∞</sup>.
   * f(n) =
     * O(g(n)) and &Omega;<sup>∞</sup>(g(n)) (if f(n) = &Theta;(g(n)))
     * O(g(n)) (if 0 &leq; f(n) &leq; cg(n))
     * &Omega;<sup>∞</sup>(g(n)) if 0 &leq; cg(n) &leq; f(n)
   * if there are finite number of possible n's such that 0 &leq; cg(n) &leq; f(n).
2. Describe the potential advantages and disadvantages of using &Omega;<sup>∞</sup> instead of &Omega; to characterize the running times of programs.
   * Advantage: We can characterize all the relationships between all functions
   * Disadvantage: We cannot characterize precisely.
   Some authors also define O in a slightly different manner; let’s use O' for the alternative definition. We say that f(n) = O'(g(n)) if and only if |f(n)| = O(g(n)).
3. What happens to each direction of the “if and only if” in Theorem 3.1 if we substitute O' for O but still use &Omega;?
   * left to right will stay true, but vice versa would be false 
   Some authors define O<sup>~</sup> (read “soft-oh”) to mean O with logarithmic factors ignored:
   O<sup>~</sup>(g(n)) = {f(n) : there exist positive constants c, k, and n<sub>0</sub> such that 0 &leq; f(n) &leq; cg(n)lg<sup>k</sup>(n) for all n &geq; n<sub>0</sub>}
4. Define &Omega;<sup>~</sup> and &Theta;<sup>~</sup>‚ in a similar manner. Prove the corresponding analog to Theorem 3.1.
   *  &Omega;<sup>~</sup>(g(n)) = {f(n) : there exists a positive constants c, k, n<sub>0</sub> such that 0 &leq; cg(n)lg<sup>k</sup>(n) &leq; f(n) for all n &geq; n<sub>0</sub>}
   *  &Theta;<sup>~</sup>(g(n)) = {f(n) : there exists a positive constants c<sub>1</sub>, c<sub>2</sub>, k<sub>1</sub>, k<sub>2</sub>, n<sub>0</sub> such that 0 &leq; c<sub>1</sub>g(n)lg<sup>k<sub>1</sub></sup>(n) &leq; f(n) &leq; c<sub>2</sub>g(n)lg<sup>k<sub>2</sub></sup>(n) for all n &geq; n<sub>0</sub>}
   *  For any two functions f(n) and g(n), we have f(n) = &Theta;<sup>~</sup>(g(n)) if and only if f(n)=O<sup>~</sup>(g(n)) and f(n)=Ω<sup>~</sup>(g(n)).

## 3-6 Iterated functions

We can apply the iteration operator \* used in the lg<sup>*</sup> function to any monotonically increasing function f(n) over the reals. For a given constant c ∈ R, we define the iterated function f<sub>c</sub><sup>*</sup> by

f<sub>c</sub><sup>*</sup>(n) = min {i &geq; 0 : f<sup>(i)</sup>(n) &leq; c},

which need not be well defined in all cases. In other words, the quantity f<sub>c</sub><sup>*</sup>(n) is the number of iterated applications of the function f required to reduce its argument down to c or less.

For each of the following functions f(n) and constants c, give as tight a bound as possible on f<sub>c</sub><sup>*</sup>(n).

|f(n)|c|f<sub>c</sub><sup>*</sup>(n)|
|---|---|---|
|n - 1|0|&Theta;(n)|
|lg n|1|&Theta;(lg<sup>*</sup>n)|
|n/2|1|&Theta;(lg n)|
|n/2|2|&Theta;(lg n)|
|√n|2|&Theta;(lg lg n)|
|√n|1|X|
|n<sup>1/3</sup>|2|&Theta;(log<sub>3</sub>lgn|
|n/lg n|2|&omega;(lg lg n), o(lg n)|
