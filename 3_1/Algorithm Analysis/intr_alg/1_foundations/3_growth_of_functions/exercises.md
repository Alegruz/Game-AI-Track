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

## 3.2-1

Show that if f(n) and g(n) are monotonically increasing functions, then so are the functions f(n) + g(n) and f(g(n)), and if f(n) and g(n) are in addition
nonnegative, then f(n) ⋅ g(n) is monotonically increasing.

* if x < y -> f(x) &leq; f(y) and if x < y -> g(x) &leq; g(y)
* thus, if x < y, f(x) + g(x) &leq; f(y) + g(y)
* thus, if x < y, g(x) &leq; g(y), if g(x) &leq; g(y), f(g(x)) &leq; f(g(y))
* if f(n), g(n) > 0, if x < y, f(x)g(x) &leq; f(y)g(y)

## 3.2-2

Prove equation (3.16).

a<sup>log<sub>b</sub>c</sup> = c<sup>log<sub>b</sub>a</sup>

* a<sup>log<sub>b</sub>c</sup>
  * a<sup>(log<sub>a</sub>c)/log<sub>a</sub>b)</sup>
  * (a<sup>log<sub>a</sub>c)</sup>)<sup>(1/log<sub>a</sub>b)</sup>
  * c<sup>(1/log<sub>a</sub>b)</sup>
  * c<sup>(1/(log<sub>b</sub>b/log<sub>b</sub>a))</sup>
  * c<sup>(1/(1/log<sub>b</sub>a))</sup>
  * * c<sup>log<sub>b</sub>a</sup>

## 3.2-3

Prove equation (3.19). Also prove that n! ≠ &omega;(2<sup>n</sup>) and n! ≠ o(n<sup>n</sup>).

log<sub>2</sub> n! = &Theta;(n log<sub>2</sub> n)

* log<sub>2</sub> n! = log<sub>2</sub>(√(2&pi;n)(n/e)<sup>n</sup>(1+&Theta;(1/n)))
  * log<sub>2</sub>(√(2&pi;n)) + log<sub>2</sub>(n/e)<sup>n</sup> + log<sub>2</sub>(1+&Theta;(1/n))
  * &Theta;(√n) + nlog<sub>2</sub>(n/e) + log<sub>2</sub>(&Theta;(1)+&Theta;(1/n))
  * &Theta;(√n) + &Theta;(nlog<sub>2</sub>n) + &Theta;(1/n)
  * &Theta;(nlog<sub>2</sub>n)

* lim<sub>n→∞</sub>(2<sup>n</sup>/n!) = lim<sub>n→∞</sub>(2<sup>n</sup>/(√(2&pi;n)(n/e)<sup>n</sup>(1+&Theta;(1/n))))
  * lim<sub>n→∞</sub>((2<sup>n</sup>/(√(2&pi;n)(1+&Theta;(1/n)))((2e/n)<sup>n</sup>)) &leq; lim<sub>n→∞</sub>((2e/n)<sup>n</sup>) &leq; lim<sub>n→∞</sub>(1/2<sup>n</sup>) = 0 (n > 4e)


* lim<sub>n→∞</sub>(n<sup>n</sup>/n!) = lim<sub>n→∞</sub>(n<sup>n</sup>/(√(2&pi;n)(n/e)<sup>n</sup>(1+&Theta;(1/n))))
  * lim<sub>n→∞</sub>(e<sup>n</sup>/(√(2&pi;n)(1+&Theta;(1/n))))
  * lim<sub>n→∞</sub>(O(1/√n)e<sup>n</sup>) &geq; lim<sub>n→∞</sub>(e<sup>n</sup>/c√n) &geq; lim<sub>n→∞</sub>(e<sup>n</sup>/cn) = ∞ (∃c > 0)

## 3.2-4 ★

Is the function ⌈log<sub>2</sub>n⌉! polynomially bounded? Is the function ⌈log<sub>2</sub>log<sub>2</sub>n⌉! polynomially bounded?

* log<sub>2</sub>(n!) = &Theta;(n log<sub>2</sub>n)
  * log<sub>2</sub>(⌈log<sub>2</sub>n⌉!) = &Theta;((⌈log<sub>2</sub>n⌉) log<sub>2</sub>(⌈log<sub>2</sub>n⌉))
    * &Theta;((log<sub>2</sub>n) log<sub>2</sub>(log<sub>2</sub>n))
    * &omega;(log<sub>2</sub>n)
    * thus, ≠ O(log<sub>2</sub> n)

* log<sub>2</sub>(⌈log<sub>2</sub>log<sub>2</sub>n⌉!) = &Theta;((⌈log<sub>2</sub>log<sub>2</sub>n⌉) log<sub>2</sub>(⌈log<sub>2</sub>log<sub>2</sub>n⌉))
  * &Theta;((log<sub>2</sub>log<sub>2</sub>n) log<sub>2</sub>(log<sub>2</sub>log<sub>2</sub>n))
  * o((log<sub>2</sub>log<sub>2</sub>n)<sup>2</sup>)
  * o(log<sub>2</sub><sup>2</sup>(log<sub>2</sub>n))
  * o(log<sub>2</sub>n)
  * O(log<sub>2</sub>n)

## 3.2-5 ★

Which is asymptotically larger: log<sub>2</sub>(log<sub>2</sub><sup>\*</sup>n) or log<sub>2</sub><sup>\*</sup>(log<sub>2</sub>n)?

* lim<sub>n→∞</sub>(log<sub>2</sub>(log<sub>2</sub><sup>\*</sup>n) / log<sub>2</sub><sup>\*</sup>(log<sub>2</sub>n)) = lim<sub>n→∞</sub>(log<sub>2</sub>(log<sub>2</sub><sup>\*</sup>2<sup>n</sup>) / log<sub>2</sub><sup>\*</sup>(log<sub>2</sub>2<sup>n</sup>))
  * lim<sub>n→∞</sub>(log<sub>2</sub>(1 + log<sub>2</sub><sup>\*</sup>n) / log<sub>2</sub><sup>\*</sup>n)
  * lim<sub>n→∞</sub>(log<sub>2</sub>(1 + n) / n) = 0

log<sub>2</sub><sup>\*</sup>(log<sub>2</sub>n) is asymptotically larger.

## 3.2-6

Show that the golden ratio &Phi; and its conjugate &Phi;<sup>^</sup> both satisfy the equation x<sup>2</sup> = x + 1.

* x<sup>2</sup> - x - 1 = 0
* x = (1 ± √(1 + 4)) / 2
  * x<sub>0</sub> = (1 + √5)) / 2 = &Phi;
  * x<sub>1</sub> = (1 - √5)) / 2 = &Phi;<sup>^</sup>

## 3.2-7

Prove by induction that the i th Fibonacci number satisfies the equality F<sub>i</sub> = &Phi;<sup>i</sup> - &Phi;<sup>^</sup><sup>i</sup> / √5, where &Phi; is the golden ratio and &Phi;<sup>^</sup> is its conjugate.

f(1) = 1
f(2) = 1
f(n) = f(n - 1) + f(n - 2)

By characteristic equations,

(f(n) - &alpha;f(n - 1)) = &beta;(f(n - 1) - &alpha;f(n - 2))

&alpha; + &beta; = 1
&alpha;&beta; = -1

thus, &alpha; = &Phi;, &beta; = &Phi;<sup>^</sup>.

(f(n + 1) - &Phi;f(n)) = &Phi;<sup>^</sup><sup>n-1</sup>(f(2) - &Phi;f(1))
(f(n + 1) - &Phi;<sup>^</sup>f(n)) = &Phi;<sup>n-1</sup>(f(2) - &Phi;<sup>^</sup>f(1))

subtract two expressions

(&Phi; - &Phi;<sup>^</sup>)f(n) = (f(2) - &Phi;<sup>^</sup>f(1))&Phi;<sup>n-1</sup> - (f(2) - &Phi;f(1))&Phi;<sup>^</sup><sup>n-1</sup>
  * (1 - &Phi;<sup>^</sup>)&Phi;<sup>n-1</sup> - (1 - &Phi;)&Phi;<sup>^</sup><sup>n-1</sup>
  * &Phi;<sup>n</sup> - &Phi;<sup>^</sup><sup>n</sup>
* f(n) = (&Phi;<sup>n</sup> - &Phi;<sup>^</sup><sup>n</sup>) / (&Phi; - &Phi;<sup>^</sup>)
  * (&Phi;<sup>n</sup> - &Phi;<sup>^</sup><sup>n</sup>) / √5

## 3.2-8

Show that k log<sub>e</sub> k = &Theta;(n) implies k = &Theta;(n / log<sub>e</sub>n)

* k log<sub>e</sub> k = &Theta;(n)
* n = &Theta;(k log<sub>e</sub> k)
  * log<sub>e</sub>n = &Theta;(log<sub>e</sub>(k log<sub>e</sub> k))
    * &Theta;(log<sub>e</sub>k + log<sub>e</sub><sup>2</sup>k)
    * &Theta;(log<sub>e</sub>k)
* n/log<sub>e</sub>n = &Theta;(k log<sub>e</sub> k)/&Theta;(log<sub>e</sub>k) = &Theta;((k log<sub>e</sub> k) / log<sub>e</sub>k) = &Theta;(k)
  * k = &Theta;(n/log<sub>e</sub>n)