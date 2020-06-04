/*
 a. element with the largest time stamp

 b. Push
	newElement = stack element with next largest time stamp	O(1)
	stack.push_back(newElement)								O(1)
															O(2) == O(1)

 	Pop
	item = first iteration of stack				O(1)
	maxItem = first element of stack			O(1)
	for (item reaches last iteration of stack)	O(n)
	{
		if (*item > maxItem)
		{
			maxItem = *item
		}
	}
	stack.remove(item)							O(1)
												O(n + 3) == O(n)

 c. Push: O(1).
	Original push merely adds a new element at the back of the stack
	Our push similarly merely adds a new element to the stack.

	Pop: O(n).
	Originial pop merely removes the last element of the stack, thus O(1).
	Our pop however, first, has to find the element of largest time stamp,
	which means it has to traverse through n elements in the stack to find the item.
	Deleting an element from a stack takes O(1), thus total of O(n + 1) == O(n)
 */

int main()
{
	return 0;
}