#ifndef SIMPLE_GRAPH_ADJMATRIX
#define SIMPLE_GRAPH_ADJMATRIX

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>

class simple_graph_adjmatrix{
	int ** vertex_matrix;
	int num_of_vertices,num_of_edges;

public:
	simple_graph_adjmatrix(int _num_of_vertices) :num_of_vertices(_num_of_vertices)
	{
		vertex_matrix = new int*[_num_of_vertices];

		for (int i = 0; i < _num_of_vertices; i++)
		{
			vertex_matrix[i] = new int[_num_of_vertices];
		}

		for (int i = 0; i < num_of_vertices; i++) 
		{
			for (int j = 0; j < num_of_vertices; j++)
				vertex_matrix[i][j] = 0;
		}

	}

	~simple_graph_adjmatrix()
	{
		for (int i = 0; i < num_of_vertices; i++)
		{
			delete[] vertex_matrix[i];
		}
		delete[] vertex_matrix;
	}

	void add_edge(int v1, int v2, int weight)
	{
		if (vertex_matrix[v1][v2] == 0)
			num_of_edges++;
		vertex_matrix[v1][v2] = weight;
	}


	void delEdge(int v1, int v2)
	{
		if (vertex_matrix[v1][v2] != 0)
			num_of_edges--;
		vertex_matrix[v1][v2] = 0;
	}
};


//class simple_graph_adjmatrix {
//private:
//
//	int numVertex, numEdge;// Store number of vertices, edges 
//	int **matrix; // Pointer to adjacency matrix 
//	int *mark;// Pointer to mark array 
//
//public:
//	simple_graph_adjmatrix(int numVert){
//		// Make graph w/ numVert vertices 
//		int i;
//		numVertex = numVert;
//		numEdge = 0;
//		mark = new int[numVert];
//
//		// Initialize mark array 
//		for (i = 0; i < numVertex; i++)
//		{
//			mark[i] = false;
//		}
//
//		matrix = (int**) new int*[numVertex];
//
//		// Make matrix 
//		for (i = 0; i < numVertex; i++)
//			matrix[i] = new int[numVertex];
//
//		for (i = 0; i < numVertex; i++) // Initialize to 0 weights 
//		{
//			for (int j = 0; j < numVertex; j++)
//				matrix[i][j] = 0;
//		}
//	}
//
//	~simple_graph_adjmatrix(){ // Destructor 
//		delete[] mark;
//		// Return dynamically allocated memory 
//		for (int i = 0; i < numVertex; i++)
//			delete[] matrix[i];
//		delete[] matrix;
//	}
//
//	int n() {
//		return numVertex;
//	}// Number of vertices 
//
//	int e() {
//		return numEdge;
//	} // Number of edges
//
//	// Set edge (v1, v2) to "wgt"
//	void setEdge(int v1, int v2, int wgt)
//	{
//		assert(wgt > 0, "Illegal weight value");
//		if (matrix[v1][v2] == 0)
//			numEdge++;
//		// Increment edge count 
//		matrix[v1][v2] = wgt;
//	}
//
//	void delEdge(int v1, int v2)
//	{
//		// Delete edge (v1, v2) 
//		if (matrix[v1][v2] != 0)
//			numEdge--;
//		matrix[v1][v2] = 0;
//	}
//
//	int weight(int v1, int v2)
//	{
//		return matrix[v1][v2];
//	}
//
//	int getMark(int v)
//	{
//		return mark[v];
//	}
//
//	void setMark(int v, int val)
//	{
//		mark[v] = val;
//	}
//
//	// Return first neighbor of "v" 
//	int first(int v)
//	{
//		for (int i = 0; i < numVertex; i++)
//		{
//			if (matrix[v][i] != 0)
//				return i;
//		}
//
//		return numVertex; // Return n if none 
//	}
//
//	// Return v1’s next neighbor after "v2" 
//	int next(int v1, int v2)
//	{
//		for (int i = v2 + 1; i < numVertex; i++)
//		{
//			if (matrix[v1][i] != 0)
//				return i;
//		}
//
//		return numVertex; // Return n if none 
//	}
//};


#endif