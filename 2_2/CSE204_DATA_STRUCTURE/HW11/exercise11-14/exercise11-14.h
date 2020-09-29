/*
 Use the following description of an undirected graphin Exercises 11–14.
 EmployeeGraph		=	(V, E)
 V(EmployeeGraph)	=	{Susan, Darlene, Mike, Fred, John, Sander, Lance, Jean, Brent, Fran}
 E(EmployeeGraph)	=	{(Susan, Darlene),	(Fred, Brent),		(Sander,  Susan), 
 						(Lance, Fran),		(Sander,  Fran),	(Fran,  John),
						(Lance, Jean),		(Jean, Susan),		(Mike, Darlene),
						(Brent, Lance),		(Susan, John)							}

 11. Draw a picture of EmployeeGraph.
 Brent - Fred
   |
 Lance - Fran - Sander
   |      |       |
  Jean	 John - Susan - Darlene - Mike
   |              |
   ----------------

 12. Draw EmployeeGraph, implemented as an adjacency matrix. Store the vertex values in alphabetical order.
 0	Brent
 1	Darlene
 2	Fran
 3	Fred
 4	Jean
 5	John
 6	Lance
 7	Mike
 8	Sander
 9	Susan

 0	0	0	0	1	0	0	1	0	0	0
 1	0	0	0	0	0	0	0	1	0	1
 2	0	0	0	0	0	1	1	0	1	0
 3	1	0	0	0	0	0	0	0	0	0
 4	0	0	0	0	0	0	1	0	0	1
 5	0	0	1	0	0	0	0	0	0	0
 6	1	0	1	0	1	0	0	0	0	1
 7	0	1	0	0	0	0	0	0	0	0
 8	0	0	1	0	0	0	0	0	0	1
 9	0	1	0	0	1	0	1	0	1	0
	0	1	2	3	4	5	6	7	8	9

 13. Using the adjacency matrix for EmployeeGraph from Exercise 12, describe the path from Susan to Lance
 a.using a breadth-first strategy.
 1.
		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 0 0 0 0 0 0 0 0 0
 Queue:
 2.
 1.
		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 0 0 0 0 0 0 0 0 1
 Queue: Susan
 3.
		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 0 0 0 0 0 0 0 0 1 
 Queue:
 Susan ->
 4.
		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 1 0 0 0 1 0 0 1 1 
 Queue: John Sander Darlene
 Susan ->
 5.
		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 1 1 0 0 1 0 0 1 1 
 Queue: Sander Darlene Fran
 Susan -> John
 6.
		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 1 1 0 0 1 0 0 1 1 
 Queue: Darlene Fran
 Susan -> John -> Sander
 7.
		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 1 1 0 0 1 0 1 1 1 
 Queue: Fran Mike
 Susan -> John -> Sander -> Darlene
 8.
 		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 1 1 0 0 1 1 1 1 1 
 Queue: Mike Lance
 Susan -> John -> Sander -> Darlene -> Fran
 9.
 		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 1 1 0 0 1 1 1 1 1 
 Queue: Lance
 Susan -> John -> Sander -> Darlene -> Fran -> Mike
 10.
 		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 1 1 0 0 1 1 1 1 1 
 Queue: 
 Susan -> John -> Sander -> Darlene -> Fran -> Mike -> Lance

 b.using a depth-first strategy.
 1.
		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 0 0 0 0 0 0 0 0 0
 Stack:
 2.
		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 0 0 0 0 0 0 0 0 1
 Stack: Susan
 Susan 
 3.
		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 0 0 0 0 1 0 0 0 1
 Stack: Susan John
 Susan -> John
 4.
 		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 0 1 0 0 1 0 0 0 1
 Stack: Susan John Fran
 Susan -> John -> Fran
 5.
  		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 0 1 0 0 1 0 0 1 1
 Stack: Susan John Fran Sander
 Susan -> John -> Fran -> Sander
 6.
 		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 0 1 0 0 1 0 0 0 1
 Stack: Susan John Fran
 Susan -> John -> Fran
 7.
  		  0 1 2 3 4 5 6 7 8 9
 Visited: 0 0 1 0 0 1 1 0 0 1
 Stack: Susan John Fran Lance
 Susan -> John -> Fran -> Lance

 14. Which one of the following phrases best describes the relationship representedby the edges between the vertices in EmployeeGraph?
 a. “works for”
 b. “is the supervisor of ”
 c. “is senior to”
 d. “works with”

 d
 */