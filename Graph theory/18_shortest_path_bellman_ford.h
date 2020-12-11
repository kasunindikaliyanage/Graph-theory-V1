#ifndef SHORTEST_PATH_16_BELLMAN_FORD
#define SHORTEST_PATH_16_BELLMAN_FORD

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <list>

enum NODE_COLOR {
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


class simple_graph {

	std::vector<vertex*> vertex_list;
	std::list<vertex*> processed_list;
	std::vector<vertex*> graph_transpose_list;

	friend bool sortest_path_bellman_ford(simple_graph&, int);
	
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

// u - start vertex 
// v - end vertex
// weight weight of the graph
void relax(vertex* u, vertex* v,int weight)
{
	if (v->distance > u->distance + weight)
	{
		v->distance = u->distance + weight;
		v->predecessor = u;
	}
}

bool sortest_path_bellman_ford(simple_graph&graph, int source_vertex_id)
{
	vertex * v1 = graph.initialize_and_find_vertex(source_vertex_id);

	if (v1 == NULL)
	{
		throw std::runtime_error("sortest_path_bellman_ford failed : cannot find source vertex with id - " + std::to_string(source_vertex_id));
	}
	else
	{
		//outer loop iterate V -1 times
		int outer_loop_count = graph.vertex_list.size() - 1;
		
		for (int i = 0; i < outer_loop_count; i++)
		{
			//iterate through all the edges
			for each (auto u in graph.vertex_list)
			{
				for each (auto v in u->adj_list)
				{
					if (u->distance != INT_MAX)
					{
						//call relax operation
						relax(u, (vertex*)v.first, v.second);
					}
				}
			}
		}

		//checking for negative weight cycles
		for each (auto u in graph.vertex_list)
		{
			for each (auto v in u->adj_list)
			{
				if (u->distance != INT_MAX)
				{
					if (v.first->distance > u->distance + v.second)
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}

#endif