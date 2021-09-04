# Exercises

## 1.1-1 Give a real-world example that require sorting or a real-world example that requires computing a convex hull.

### Sorting

When we need to sort certain events that a game has to deal by priority, we need some sort of sorting technique.

### Convex Hull

When developing a strategy game based on nodes, we need to compute which area can be a legitimate boundary. Using convex hull provides the smallest area that such nodes can create.

## 1.1-2 Other than speed, what other measures of efficiency might one use in a real-world setting?

If one cannot provide sufficient memory resource, we have to trade speed for memory efficiency. This is especially true in embedded systems.

## 1.1-3 Select a data structure that you have seen previously, and discuss its strengths and limitations

Array.

Array can fetch a element in a constant time provided that one has its index. Array has a continuous memory which helps speed due to CPU cache. However, due to this characteristic, insertion and removal requires items to either push front or pull back, causing linear time operation.

## 1.1-4 How are the shortest-path and traveling-salesman problems given above similar? How are they different?

Both requires shortest path given starting point and destination point. However, in shortest-path problem, starting point and destination point are different, and the path doesn't require intermediary nodes. Traveling-salesman has certain nodes that the salesman must pass, and he/she must start and return to the same node.

## 1.1-5 Come up with a real-world problem in which only the best solution will do. Then come up with one in which a solution that is "approximately" the best is good enough

Find the global optimum of a convex function such as x<sup>2</sup>. Use gradient descent algorithm to find the optimum.

## 1.2-1 Give an example of an application that requires algorithmic content at the applciation level, and discuss the function of the algorithms involved

Every time a frame updates in a game, the renderer of the game must draw a triangle on Cartesian coordinate, requiring some form of algorithm suited for computational geometry such as DDA algorithm.

## 1.2-2 Suppose we are comparing implementations of insertion sort and merge sort on the same machine. For inputs of size *n*, insertion sort runs in 8*n*<sup>2</sup> steps, while merge sort runs in 64*n log n* steps. For which values of *n* does insertion sort beat merge sort?

1. 8*n*<sup>2</sup> - 64*n log n* < 0
2. 8*n* × (*n* - 8 *log n*) < 0
3. (*n* - 8 *log n*) < 0 (∵ 8 > 0 and *n* > 0)
4. (*log* 2<sup>*n*</sup> - *log n*<sup>8</sup>) < 0
5. *log* 2<sup>*n*</sup> < *log n*<sup>8</sup>
6. 2<sup>*n*</sup> < *n*<sup>8</sup> (∵ *log* is a monotone increasing function)
7. When n is between 2 and 43, insertion sort is faster than merge sort.

## 1.2-3 What is the smallest value of *n* such that an algorithm whose running time is 100*n*<sup>2</sup> runs faster than an algorithm whose running time is 2<sup>*n*</sup> on the same machine?

15
