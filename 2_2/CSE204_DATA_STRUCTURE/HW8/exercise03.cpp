/*
1. Is there a nonrecursive base case?
	1. when list.info[startIndex] == value
	2. when startIndex == list.length-1

2. Does each recursive call involve a smaller case of the problem?
yes. by returning startIndex + 1, it leaves the rest of the list to be searched

3. Assuming that the recursive calls succeed, does the entire function work?
unless list is initialized and the given startIndex doesn't exceed the index limit of list,info, the function should work.
When the recursion hits the base case, or it starts off with a base case, if we find it, then it returns true, and vice versa.

 */