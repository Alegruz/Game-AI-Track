#pragma once
#include "QueType.h"

template <class VertexType>
// Assumption: VertexType is a type for which the "=",
// "==", and "<<" operators are defined
class GraphType
{
public:
	GraphType();		 // Default of 50 vertices
	GraphType(int maxV); // maxV <= 50
	~GraphType();
	//  void MakeEmpty();
	//  bool IsEmpty() const;
	//  bool IsFull() const;
	void AddVertex(VertexType);
	void AddEdge(VertexType, VertexType, int);
	int WeightIs(VertexType, VertexType);
	void GetToVertices(VertexType, QueType<VertexType>&);
	void DeleteEdge(const VertexType& fromVertex, const VertexType& toVertex);
	bool DepthFirstSearch(const VertexType& startVertex, const VertexType& endVertex) const;
	//  void ClearMarks();
	//  void MarkVertex(VertexType);
	//  bool IsMarked(VertexType);
private:
	int mNumVertices;
	int mMaxVertices;
	VertexType* mVertices;
	int mEdges[50][50];
	bool* mMarks; // marks[i] is mark for vertices[i].
	bool DepthFirstSearchRecursive(const VertexType& startVertex, const VertexType& endVertex) const;
};

template<class VertexType>
GraphType<VertexType>::GraphType()
// Post: Arrays of size 50 are dynamically allocated for  
//       marks and vertices.  numVertices is set to 0; 
//       maxVertices is set to 50.
{
	mNumVertices = 0;
	mMaxVertices = 50;
	mVertices = new VertexType[50];
	mMarks = new bool[50];
}

template<class VertexType>
GraphType<VertexType>::GraphType(int maxV)
// Post: Arrays of size maxV are dynamically allocated for  
//       marks and vertices.  
//       numVertices is set to 0; maxVertices is set to maxV.
{
	mNumVertices = 0;
	mMaxVertices = maxV;
	mVertices = new VertexType[maxV];
	mMarks = new bool[maxV](false);
}

template<class VertexType>
// Post: arrays for vertices and marks have been deallocated.
GraphType<VertexType>::~GraphType()
{
	delete [] mVertices;
	delete [] mMarks;
}
const int NULL_EDGE = 0;

template<class VertexType>
void GraphType<VertexType>::AddVertex(VertexType vertex)
// Post: vertex has been stored in vertices.
//       Corresponding row and column of edges has been set 
//       to NULL_EDGE.
//       numVertices has been incremented.
{
	mVertices[mNumVertices] = vertex;

	for (int index = 0; index < mNumVertices; index++)
	{
		mEdges[mNumVertices][index] = NULL_EDGE;
		mEdges[index][mNumVertices] = NULL_EDGE;
	}
	mNumVertices++;
}

template<class VertexType>
int IndexIs(VertexType* vertices, VertexType vertex)
// Post: Returns the index of vertex in vertices.
{
	int index = 0;

	while (!(vertex == vertices[index]))
	{
		index++;  
	}
	return index;
}       

template<class VertexType>
void GraphType<VertexType>::AddEdge(VertexType fromVertex,
     VertexType toVertex, int weight)
// Post: Edge (fromVertex, toVertex) is stored in edges.
{
	size_t row = IndexIs(mVertices, fromVertex);
	size_t column = IndexIs(mVertices, toVertex);
	mEdges[row][column] = weight;
}

template<class VertexType>
int GraphType<VertexType>::WeightIs
     (VertexType fromVertex, VertexType toVertex)
// Post: Returns the weight associated with the edge 
//       (fromVertex, toVertex).
{
	size_t row = IndexIs(mVertices, fromVertex);
	size_t column = IndexIs(mVertices, toVertex);
	return mEdges[row][column];
}

template<class VertexType>
void GraphType<VertexType>::GetToVertices(VertexType vertex, QueType<VertexType>& adjVertices)
// Post: 
{
	int fromIndex = IndexIs(mVertices, vertex);
	for (size_t toIndex = 0; toIndex < static_cast<size_t>(mNumVertices); toIndex++)
	{
		if (mEdges[fromIndex][toIndex] != NULL_EDGE)
		{
			adjVertices.Enqueue(mVertices[toIndex]);
		}
	}
}

template<class VertexType>
void GraphType<VertexType>::DeleteEdge(const VertexType& fromVertex, const VertexType& toVertex)
{
	size_t row = IndexIs(mVertices, fromVertex);
	size_t column = IndexIs(mVertices, toVertex);
	mEdges[row][column] = 0;
}

template<class VertexType>
bool GraphType<VertexType>::DepthFirstSearch(const VertexType& startVertex, const VertexType& endVertex) const
{
	for (size_t i = 0; i < static_cast<size_t>(mNumVertices); ++i)
	{
		mMarks[i] = false;
	}

	bool bResult = DepthFirstSearchRecursive(startVertex, endVertex);
	
	std::cout << std::endl;
	return bResult;
}

template<class VertexType>
bool GraphType<VertexType>::DepthFirstSearchRecursive(const VertexType& startVertex, const VertexType& endVertex) const
{
	// std::cout << "DEPTHFIRSTSEARCH: Called with startVertex \"" << startVertex << "\" and endVertex \"" << endVertex << "\"" << std::endl;
	QueType<VertexType> vertexQueue;
	if (startVertex == endVertex)
	{
		// std::cout << "DEPTHFIRSTSEARCH: Found vertex " << endVertex << std::endl;
		std::cout << endVertex;

		return true;
	}

	for (size_t i = 0; i < static_cast<size_t>(mNumVertices); ++i)
	{
		// std::cout << "DEPTHFIRSTSEARCH: " << startVertex << " vs " << mVertices[i] << " = " << mEdges[IndexIs(mVertices, startVertex)][i] << std::endl;
		if (mEdges[IndexIs(mVertices, startVertex)][i] > 0 && mMarks[i] == false)
		{
			// std::cout << "DEPTHFIRSTSEARCH: Appending adjacent vertex: " << mVertices[i] << std::endl;
			vertexQueue.Enqueue(mVertices[i]);
		}
	}

	VertexType vertex;
	while (!vertexQueue.IsEmpty())
	{
		vertexQueue.Dequeue(vertex);
		mMarks[IndexIs(mVertices, vertex)] = true;
		// std::cout << "DEPTHFIRSTSEARCH: Search loop initiated with vertex: " << vertex << std::endl;
		if (vertex != startVertex)
		{
			if (DepthFirstSearchRecursive(vertex, endVertex))
			{
				std::cout << " <- " << vertex;
				return true;
			}
		}
	}

	return false;
}