#ifndef SIMPLE_GRAPH_15
#define SIMPLE_GRAPH_15

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <list>

enum NODE_COLOR{
	WHITE, GRAY, BLACK
};

struct vertex {

	int node_id;
	std::string value;
	std::vector<std::pair<vertex*, int>> adj_list;

	NODE_COLOR color = WHITE;
	int distance = INT_MAX;
	vertex * predecessor = NULL;

	vertex() {}

	vertex(int _id, std::string _value = "") :node_id(_id), value(_value)
	{}

	void print_vertex()
	{
		std::cout << "Vertex id : " + std::to_string(node_id)
			+ ", value : " + value
			+ ", color : " + std::to_string(color)
			+ ", distance :" + std::to_string(distance)
			+ ", predecessor_id : ";
		if (predecessor != NULL)
			std::cout << predecessor->node_id;
		std::cout << std::endl;
	}
};

class simple_graph{

	std::vector<vertex*> vertex_list;
	std::list<vertex*> processed_list;
	std::vector<vertex*> graph_transpose_list;
	
	bool ADD_TO_PROCESSED_LIST = false;
	bool PRINT_WHILE_DFS = false;
	
	friend void DFS(simple_graph&, int);
	friend void topological_sort(simple_graph&, int);

	friend void strongly_connected_components(simple_graph&);

	vertex* initialize_and_find_vertex(int vertex_id)
	{
		vertex * v1 = NULL;

		for each (auto vertex1 in vertex_list)
		{
			vertex1->color = WHITE;
			vertex1->distance = INT_MAX;
			vertex1->predecessor = NULL;

			if (vertex1->node_id == vertex_id)
			{
				v1 = vertex1;
				v1->distance = 0;
			}
		}
		return v1;
	}

	void depth_first_search(vertex* v)
	{
		v->color = GRAY;

		if(PRINT_WHILE_DFS)
			std::cout << "(" << v->node_id <<" ";

		for each (auto adj_vetex in v->adj_list)
		{
			if (adj_vetex.first->color == WHITE)
			{
				adj_vetex.first->distance = v->distance + 1;
				adj_vetex.first->predecessor = v;
				depth_first_search((vertex*)(adj_vetex.first));
			}
		}

		if (PRINT_WHILE_DFS)
			std::cout << " " << v->node_id << ")";

		v->color = BLACK;
		//add the vertex to front of the list if flag is set
		if (ADD_TO_PROCESSED_LIST)
			processed_list.push_front(v);
	}

	void get_transpose()
	{
		for each (auto var in vertex_list)
		{
			graph_transpose_list.push_back(new vertex(var->node_id,var->value));
		}

		for each (auto var in vertex_list)
		{
			for each (auto var2 in var->adj_list)
			{
				int v1_id = var2.first->node_id;
				int v2_id = var->node_id;
				int weight = var2.second;
				vertex * v1 = NULL;
				vertex * v2 = NULL;

				bool found_v1 = false;
				bool found_v2 = false;

				for each (auto var in graph_transpose_list) {
					if (var->node_id == v1_id) {
						v1 = var;
						found_v1 = true;
					}

					if (var->node_id == v2_id) {
						v2 = var;
						found_v2 = true;
					}

					if (found_v1 && found_v2)
						break;
				}

				if (found_v1&& found_v2) {
					bool edge_already_exist = false;

					for each(auto var in v1->adj_list) {
						if (var.first->node_id == v2_id) {
							edge_already_exist = true;
							throw std::runtime_error("Failed adding edge : " + std::to_string(v1_id) + " - " + std::to_string(v2_id) + " edge already exsits");
							break;
						}
					}
					if (!edge_already_exist) {
						v1->adj_list.push_back(std::make_pair(v2, weight));
					}

				}
			}
		}
	}

	void delete_transpose()
	{
		for each (auto var in graph_transpose_list) {
			delete var;
		}
	}

public:
	simple_graph()
	{}

	~simple_graph() {
		for each (auto var in vertex_list) {
			delete var;
		}
	}

	void add_node(int _node_id, std::string value = "") {
		for each (auto var in vertex_list) {
			if (var->node_id == _node_id) {
				throw std::runtime_error("Failed adding node : node with node_id -" + std::to_string(_node_id) + " already exsits in graph");
			}
		}
		vertex_list.push_back(new vertex(_node_id, value));
	}

	void add_edge(int v1_id, int v2_id, int weight = 0) {
		vertex * v1 = NULL;
		vertex * v2 = NULL;

		bool found_v1 = false;
		bool found_v2 = false;

		for each (auto var in vertex_list) {
			if (var->node_id == v1_id) {
				v1 = var;
				found_v1 = true;
			}

			if (var->node_id == v2_id) {
				v2 = var;
				found_v2 = true;
			}

			if (found_v1 && found_v2)
				break;
		}

		if (found_v1&& found_v2) {
			bool edge_already_exist = false;

			for each(auto var in v1->adj_list) {
				if (var.first->node_id == v2_id) {
					edge_already_exist = true;
					throw std::runtime_error("Failed adding edge : " + std::to_string(v1_id) + " - " + std::to_string(v2_id) + " edge already exsits");
					break;
				}
			}
			if (!edge_already_exist) {
				v1->adj_list.push_back(std::make_pair(v2, weight));
			}

		}
		else {
			throw std::runtime_error("Failed adding edge : one or both vertex does not exsits");
		}
	}

	void print_graph() {
		for each (auto vertex1 in vertex_list) {
			for each(auto vertex2 in vertex1->adj_list) {
				std::cout << vertex1->node_id << " - " << vertex2.first->node_id << std::endl;
			}
		}
	}

	void print_nodes()
	{
		for each (auto var in vertex_list) {
			var->print_vertex();
		}
	}
};

void DFS(simple_graph& graph, int source_vertex_id = -1)
{
	if (source_vertex_id != -1)
	{
		vertex * v1 = graph.initialize_and_find_vertex(source_vertex_id);

		if (v1 == NULL)
		{
			throw std::runtime_error("DFS failed : cannot find source vertex with id - " + std::to_string(source_vertex_id));
		}
		else
		{
			//call depth_first_search fucntion with source vertex
			graph.depth_first_search(v1);
		}
	}

	for each (auto v1 in graph.vertex_list)
	{
		if (v1->color == WHITE)
		{
			v1->distance = 0;
			graph.depth_first_search(v1);
		}
	}
}

void topological_sort(simple_graph& graph, int source_id)
{
	graph.processed_list.clear();
	graph.ADD_TO_PROCESSED_LIST = true;
	DFS(graph, source_id);
	graph.ADD_TO_PROCESSED_LIST = false;

	/*for each (auto v in graph.processed_list)
	{
		v->print_vertex();
	}*/

}

void strongly_connected_components(simple_graph& graph)
{
	graph.PRINT_WHILE_DFS = false;
	
	topological_sort(graph,-1);
		
	//get the transpose graph
	graph.get_transpose();
	
	graph.PRINT_WHILE_DFS = true;
	
	//picking vertex in order they appear at the processed list
	for each (auto var in graph.processed_list)
	{
		// runing dfs on transpose graph
		for each (auto var2 in graph.graph_transpose_list)
		{
			if ((var->node_id == var2->node_id) && var2->color == WHITE)
			{
				graph.depth_first_search(var2);
				std::cout << std::endl;
				break;
			}
		}
	}

	std::cout << "End of pinting component list" << std::endl;

	//while constructing transpose we created vertices object on heap
	//so we have to reclain it, otherwise memory leak will occur
	graph.delete_transpose();
}

#endif