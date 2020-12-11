#ifndef MST_PRIMS_25
#define MST_PRIMS_25

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <memory>

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

struct edge {
	vertex* start;
	vertex* end;
	int weight;

	edge(vertex* _start, vertex* _end, int _weight)
		:start(_start), end(_end), weight(_weight)
	{}
};

class simple_graph {

	std::vector<vertex*> vertex_list;
	std::list<vertex*> processed_list;

	bool ADD_TO_PROCESSED_LIST = false;

	friend void DFS(simple_graph&, int);

	friend void mst_prims(simple_graph&,int);

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
		for each (auto adj_vetex in v->adj_list)
		{
			if (adj_vetex.first->color == WHITE)
			{
				adj_vetex.first->distance = v->distance + 1;
				adj_vetex.first->predecessor = (vertex*)v;
				depth_first_search((vertex*)(adj_vetex.first));
			}
		}

		v->color = BLACK;
		//add the vertex to front of the list if flag is set
		if (ADD_TO_PROCESSED_LIST)
			processed_list.push_front(v);
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

int find_set(int * vertex_map, int v)
{
	return vertex_map[v - 1];
}

void mst_prims(simple_graph& graph,int source_vertex_id)
{
	vertex* v1 = graph.initialize_and_find_vertex(source_vertex_id);

	int * vertex_map = new int[graph.vertex_list.size()];
	//set vertex sets to its value initially
	for each (auto var1 in graph.vertex_list) {
		for each(auto var2 in var1->adj_list)
		{
			vertex_map[(var1->node_id) - 1] = var1->node_id;
			vertex_map[(var2.first->node_id) - 1] = var2.first->node_id;
		}
	}
	// our min priority queue which is going to store the edge
	class prioritize 
	{ 
		public: bool operator ()(edge* e1, edge* e2) 
		{ 
			return e1->weight > e2->weight;
		} 
	};
	std::priority_queue<edge*, std::vector<edge*>, prioritize> pq;



	//push edges leaving source vertice before the iteration begins
	for each (auto var in v1->adj_list)
	{
		// remember to reclaim the memory allocate for edge list
		// but dont delete vertice pointers
		pq.push(new edge(v1, var.first, var.second));
	}

	std::vector<edge*> min_spaning_tree;
	int min_spaning_tree_cost = 0;

	while (!pq.empty())
	{
		edge* temp = pq.top();
		pq.pop();

		//find the end vertice sets
		int v1_set = find_set(vertex_map, temp->start->node_id);
		int v2_set = find_set(vertex_map, temp->end->node_id);

		if (v1_set != v2_set)
		{
			min_spaning_tree.push_back(temp);
			//if the condition pass v2 is always a single vertex 
			vertex_map[temp->end->node_id-1] = v1_set;
			min_spaning_tree_cost += temp->weight;

			//and edges leaving 
			for each (auto var in temp->end->adj_list)
			{
				pq.push(new edge(temp->end, var.first, var.second));
			}
		}
	}

	for each (auto var in min_spaning_tree)
	{
		std::cout << var->start->node_id << "---" << var->end->node_id << std::endl;
	}

	std::cout << "Total weight of MST is - " << min_spaning_tree_cost << std::endl;
}

#endif
