#ifndef MST_24
#define MST_24

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
	friend void mst_kruskals(simple_graph&);


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

void union_sets(int set_1, int set_2, int * vertex_map,int size)
{
	for (int i=0; i < size; i++)
	{
		if (vertex_map[i] == set_2)
			vertex_map[i] = set_1;
	}
}

void mst_kruskals(simple_graph& graph)
{
	//array which contains vertex set
	//index of the array is same as vertex _id-1
	int * vertex_set = new int[graph.vertex_list.size()];

	class prioritize
	{
		public: bool operator ()(edge* e1, edge* e2) 
		{
			return e1->weight > e2->weight; 
		}
	};
	std::priority_queue<edge*, std::vector<edge*>, prioritize> pq;

	//make set
	for each (auto var1 in graph.vertex_list) {
		vertex_set[(var1->node_id) - 1] = var1->node_id;
		for each(auto var2 in var1->adj_list)
		{
			// create new edge and push to the pq
			// rememer to claim the memory without deleting vertex objects
			pq.push(new edge(var1, var2.first, var2.second));
		}
	}


	std::vector<edge*> min_spaning_tree;
	std::vector<edge*> ignord_list;
	int min_spaning_tree_cost = 0;

	while (!pq.empty())
	{
		edge* temp = pq.top();
		pq.pop();

		//get the sets which end vertices of this edge belongs to
		int v1_set = find_set(vertex_set, temp->start->node_id);
		int v2_set = find_set(vertex_set, temp->end->node_id);

		//compare the sets of end vertices
		if (v1_set != v2_set)
		{
			min_spaning_tree.push_back(temp);
			//union the sets that end vertices belongs to
			union_sets(v1_set, v2_set, vertex_set,graph.vertex_list.size());
			min_spaning_tree_cost += temp->weight;
		}
	}

	for each (auto var in min_spaning_tree)
	{
		std::cout << var->start->value << "---" << var->end->value << std::endl;
	}

	std::cout << "Total weight of MST is - " << min_spaning_tree_cost << std::endl;
}

#endif