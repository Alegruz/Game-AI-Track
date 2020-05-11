/*

a. list1 -> <John, 4> -> <Nell, 8> -> <Susan, 9> -> <Susanne, NULL>

b. list2 -> <Mark, 5> -> <Naomi, 6> -> <Robert, NULL>

c. 7 -> 2 -> 3

d.

free 7
| nodes | .info | .next |
|  [0]  |  John |   8   |
|  [1]  |  Mark |   5   |
|  [2]  |       |   3   |
|  [3]  |       |   4   |
|  [4]  |       |  NUL  |
|  [5]  | Naomi |   6   |
|  [6]  | Robert|  NUL  |
|  [7]  |       |   2   |
|  [8]  | Susan |   9   |
|  [9]  |Susanne|  NUL  |
list1 0
list2 1

e. 
free 7
| nodes | .info | .next |
|  [0]  |  John |   8   |
|  [1]  |  Mark |   5   |
|  [2]  |       |   3   |
|  [3]  |       |  NUL  |
|  [4]  |  Anne |  NUL  |
|  [5]  | Naomi |   6   |
|  [6]  | Robert|   4   |
|  [7]  |       |   2   |
|  [8]  | Susan |   9   |
|  [9]  |Susanne|  NUL  |
list1 0
list2 1

 */