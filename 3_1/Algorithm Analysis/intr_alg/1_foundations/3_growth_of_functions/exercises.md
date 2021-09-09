# Exercises

## 3.1-1

Let f(n) and g(n) be asymptotically nonnegative functions. Using the basic definition of &Theta;-notation, prove that max(f(n), g(n)) =  &Theta;(f(n) + g(n)).

* 0 &leq; c<sub>1</sub>(f(n) + g(n)) &leq; h(n) &leq; c<sub>2</sub>(f(n) + g(n))
  * (f(n) + g(n)) &leq; 2max(f(n), g(n))
  * (f(n) + g(n)) / 2 &leq; max(f(n), g(n))
  * max(f(n), g(n)) &leq; (f(n) + g(n))
  * (f(n) + g(n)) / 2 &leq; max(f(n), g(n)) &leq; (f(n) + g(n))
  * 0 &leq; (f(n) + g(n)) / 2 &leq; max(f(n), g(n)) &leq; (f(n) + g(n))
    * c<sub>1</sub> = 1/2, c<sub>2</sub> = 1
    * h(n) = max(f(n), g(n))

## 3.1-2

Show that for any real constants a and b, where b > 0,

(n + a)<sup>b</sup> = &Theta;(n<sup>b</sup>). (3.2)

* if |a| &leq; n
  * n + a &leq; n + |a| &leq; 2n
* if |a| &leq; n/2
  * n + a &geq; n - |a| &geq; n/2
* if n &geq; 2|a|
  * 0 &leq; n/2 &leq; n + a &leq; 2n
  * 0 &leq; (1/2)<sup>b</sup>n<sup>b</sup> &leq; (n + a)<sup>b</sup> &leq; 2<sup>b</sup>n<sup>b</sup>
    * c<sub>1</sub> = (1/2)<sup>b</sup>, c<sub>2</sub> = 2<sup>b</sup>

## 3.1-3

Explain why the statement, “The running time of algorithm A is at least O(n<sup>2</sup>),” is meaningless.

* T<sub>A</sub>(n) &geq; O(n<sup>2</sup>)
* ∃f(n) : f(n) = O(n<sup>2</sup>), T<sub>A</sub> &geq; f(n)
  * f(n) can be 0, and it is O(n<sup>2</sup>)

There are a ton of different funtions that have growth rate less than or equal to n<sup>2</sup>. In particular, functions that are constant or shrink to zero arbitrarily fast. Saying that you grow more quickly than a function that shrinks to zero quickly means nothing.

## 3.1-4

Is 2<sup>n + 1</sup> = O(2<sup>n</sup>)? Is 2<sup>2n</sup> = O(2<sup>n</sup>)?

* 0 &leq; f(n) &leq; cg(n)
* 2<sup>n + 1</sup> = 2 2<sup>n</sup> &leq; c2<sup>n</sup> (c &geq; 2)
  * yes
* 2<sup>2n</sup> &leq; c2<sup>n</sup> (c &leq; 2<sup>n</sup>)
  * even though we can find a specific constant that is greater or equal to some n, there is none that is greater or equal to any n.

## 3.1-5

Prove Theorem 3.1.

### left to right

* f(n) = &Theta;(g(n))
  * ∃c<sub>1</sub>, c<sub>2</sub>, n<sub>0</sub>: 0 &leq; c<sub>1</sub>(g(n)) &leq; f(n) &leq; c<sub>2</sub>g(n) (n &geq; n<sub>0</sub>)
  * -> ∃c<sub>1</sub>, n<sub>0</sub> 0 &leq; c<sub>1</sub>(g(n)) &leq; f(n) (n &geq; n<sub>0</sub>) -> &Omega;(g(n))
  * -> ∃c<sub>2</sub>, n<sub>0</sub> 0 &leq; f(n) &leq; c<sub>2</sub>g(n) (n &geq; n<sub>0</sub>) -> O(g(n))

### right to left

* f(n) = &Omega;(g(n))
  * ∃c<sub>1</sub>, n<sub>0</sub> : 0 &leq; c<sub>1</sub>(g(n)) &leq; f(n) (n &geq; n<sub>0</sub>)
* f(n) = O(g(n))
  * ∃c<sub>2</sub>, n<sub>1</sub> : 0 &leq; f(n) &leq; c<sub>2</sub>g(n) (n &geq; n<sub>1</sub>)
* -> ∃c<sub>1</sub>, c<sub>2</sub>, max(n<sub>0</sub>, n<sub>1</sub>) : 0 &leq; c<sub>1</sub>(g(n)) &leq; f(n) &leq; c<sub>2</sub>g(n) (n &geq; max(n<sub>0</sub>, n<sub>1</sub>))

## 3.1-6

Prove that the running time of an algorithm is &Theta;(g(n)) if and only if its worst-case running time is O(g(n)) and its best-case running time is &Omega;(g(n)).

* T(n): running time
* T<sub>w</sub>: worst-case running time
  * T(n) &leq; T<sub>w</sub>(n)
  * ∃w : wT(n) = T<sub>w</sub>(n) (w &geq; 0)
* T<sub>b</sub>: best-case running time
  * T<sub>b</sub>(n) &leq; T(n)
  * ∃b : T(n) = bT<sub>b</sub>(n) (b &geq; 0)

### left to right

* T(n) = &Theta;(g(n))
  * T(n) = O(g(n))
    * 0 &leq; T(n) &leq; cg(n)
    * 0 &leq; wT(n) &leq; wcg(n)
    * wT(n) = O(g(n))
    * T<sub>w</sub>(n) = O(g(n))
  * T(n) = &Omega;(g(n))
    * 0 &leq; cg(n) &leq; T(n)
    * 0 &leq; cg(n) &leq; bT(b)
    * 0 &leq; (c/b)g(n) &leq; T(b)
    * T(b) = &Omega;(g(n))

### right to left
* T<sub>w</sub>(n) = O(g(n))
  * ∃c<sub>1</sub>, n<sub>0</sub> : 0 &leq; T<sub>w</sub>(n) &leq; c<sub>1</sub>g(n) (n &geq; n<sub>0</sub>)
  * 0 &leq; (1/w)T<sub>w</sub>(n) &leq; (c<sub>1</sub>/w)g(n) (n &geq; n<sub>0</sub>)
  * 0 &leq; T(n) &leq; (c<sub>1</sub>/w)g(n) (n &geq; n<sub>0</sub>)
    * T(n) = O(g(n))
* T<sub>b</sub>(n) = &Omega;(g(n))
  * ∃c<sub>2</sub>, n<sub>1</sub> : 0 &leq; c<sub>2</sub>g(n) &leq; T<sub>b</sub>(n) (n &geq; n<sub>1</sub>)
  * 0 &leq; (c<sub>2</sub>/b)g(n) &leq; (1/b)T<sub>b</sub>(n) (n &geq; n<sub>1</sub>)
  * 0 &leq; (c<sub>2</sub>/b)g(n) &leq; T(n) (n &geq; n<sub>1</sub>)
    * T(n) = &Omega;(g(n))
* T(n) = &Theta;(g(n))

## 3.1-7

Prove that o(g(n)) ∩ &omega;(g(n)) is the empty set.

* assume ∃f(n) : f(n) = o(g(n)) and &omega;(g(n))
  * f(n) = o(g(n))
    * ∃n<sub>0</sub> > 0, for any c<sub>1</sub> : 0 &leq; f(n) < c<sub>1</sub>g(n) (n &geq; n<sub>0</sub>)
  * f(n) = &omega;(g(n))
    * ∃n<sub>1</sub> > 0, for any c<sub>2</sub> : 0 &leq; c<sub>2</sub>g(n) < f(n) (n &geq; n<sub>1</sub>)
  * put n<sub>2</sub> = max(n<sub>0</sub>, n<sub>1</sub>)
    * 0 &leq; c<sub>2</sub>g(n) < f(n) < c<sub>1</sub>g(n) (n &geq; n<sub>1</sub>)
    * thus, c<sub>2</sub> < c<sub>1</sub>
    * but this contradicts the fact that they are any positive constant.

## 3.1-8

We can extend our notation to the case of two parameters n and m that can go to infinity independently at different rates. For a given function g(n, m), we denote by O(g(n, m)) the set of functions O(g(n, m)) = {f(n, m) : there exist positive constants c, n<sub>0</sub>, and m<sub>0</sub> such that 0 &leq; f(n, m) &leq; cg(n, m) for all n &geq; n<sub>0</sub> or m &geq; m<sub>0</sub>}.

Give corresponding definitions for &Omega;(g(n, m)) and &Theta;(g(n, m)).

&Omega;(g(n, m)) = {f(n, m) : there exist positive constants c, n<sub>0</sub>, and m<sub>0</sub> such that 0 &leq; cg(n, m) &leq; f(n, m) for all n &geq; n<sub>0</sub> or m &geq; m<sub>0</sub>}.

&Theta;(g(n, m)) = {f(n, m) : there exist positive constants c<sub>1</sub>, c<sub>2</sub>, n<sub>0</sub>, and m<sub>0</sub> such that 0 &leq; c<sub>1</sub>g(n, m) &leq; f(n, m) &leq; c<sub>2</sub>g(n, m) for all n &geq; n<sub>0</sub> or m &geq; m<sub>0</sub>}.
