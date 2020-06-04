/*
 a.
 Base Case 1.
 if vertex to find and vertex to start is the same thus we found the vertex, stop. 

 Base Case 2.
 If there is no more vertices to check and we failed to find the vertex, stop.

 */

#include <cassert>
#include <iostream>
#include "GraphType.h"

int main()
{
	GraphType<const char*> graph;

	graph.AddVertex("dog");
	graph.AddVertex("cat");
	graph.AddVertex("animal");
	graph.AddVertex("vertebrate");
	graph.AddVertex("oyster");
	graph.AddVertex("shellfish");
	graph.AddVertex("invertebrate");
	graph.AddVertex("crab");
	graph.AddVertex("poodle");
	graph.AddVertex("monkey");
	graph.AddVertex("banana");
	graph.AddVertex("dalmatian");
	graph.AddVertex("dachshund");

	graph.AddEdge("vertebrate", "animal", 10);
	graph.AddEdge("invertebrate", "animal", 20);
	graph.AddEdge("dog", "vertebrate", 30);
	graph.AddEdge("cat", "vertebrate", 40);
	graph.AddEdge("monkey", "vertebrate", 50);
	graph.AddEdge("shellfish", "invertebrate", 60);
	graph.AddEdge("crab", "shellfish", 70);
	graph.AddEdge("oyster", "invertebrate", 80);
	graph.AddEdge("poodle", "dog", 90);
	graph.AddEdge("dalmatian", "dog", 100);
	graph.AddEdge("dachshund", "dog", 110);

	assert(graph.WeightIs("vertebrate", "animal") == 10);
	assert(graph.WeightIs("poodle", "dog") == 90);

	graph.DeleteEdge("poodle", "dog");
	assert(graph.WeightIs("poodle", "dog") == 0);

	QueType<const char*> queue;
	graph.GetToVertices("dog", queue);

	while (!queue.IsEmpty())
	{
		const char* item;
		queue.Dequeue(item);
		std::cout << item << std::endl;
	}

	return 0;
}