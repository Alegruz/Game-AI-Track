#include "GraphType.h"
#include <iostream>

template<class VertexType>
void DepthFirstSearch(GraphType<VertexType> graph, VertexType startVertex, VertexType endVertex)
// Assumes VertexType is a type for which the �==� and "<<"  
// operators are defined
{
	using namespace std;
	StackType<VertexType> stack;
	QueType<VertexType> vertexQ;

	bool bFound = false;
	VertexType vertex;
	VertexType item;

	graph.ClearMarks();
	stack.Push(startVertex);
	do
	{
		stack.Pop(vertex);
		if (vertex == endVertex)
		{
			cout << vertex;
			bFound = true;
		}
		else
		{
			if (!graph.IsMarked(vertex))
			{
			graph.MarkVertex(vertex);
			cout << vertex;
			graph.GetToVertices(vertex, vertexQ);

				while (!vertexQ.IsEmpty())
				{
					vertexQ.Dequeue(item);
					if (!graph.IsMarked(item))
					stack.Push(item);
				}
			}
		}                
	} while (!stack.IsEmpty() && !bFound);

	if (!bFound)
	{
		cout << "Path not found." << endl;
	}
}
