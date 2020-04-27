/*
15. Give the values of the following expressions:
	a. ptr1->info					30
	b. ptr2->next->info				90
	c. listData->next->next->info	45

16. Are the following expressions true or false?
	a. listData->next	== ptr1		true
	b. ptr1->next->info	== 60		false
	c. ptr2->next		== NULL		false
	d. listData->info	== 25		true

17. Decide whether the syntax of each of the following statements is valid or invalid. If it is valid, mark it as such; if it is invalid, explain what is wrong.
	a.listData->next = ptr1->next;		valid
	b.listData->next = *(ptr2->next);	invalid. cannot convert pointer into NodeType<ItemType>
	c.*listData = ptr2;					invalid. *listData is an rvalue.
	d.ptr2 = ptr1->next->info;			invalid. cannot convert ItemType into pointer
	e.ptr1->info = ptr2->info;			valid.
	f.ptr2 = ptr2->next->next;			valid.

18. Write onestatement to do each of the following:
	a.Make listData point to the node containing 45.
		listData = ptr1->next;
	b.Make ptr2 point to the last node in the list.
		ptr2 = ptr2->next;
	c.Make listData point to an empty list.
		listData = nullptr;
	d.Set the info member of the node containing 45 to 60.
		ptr1->next->info = 60;
*/