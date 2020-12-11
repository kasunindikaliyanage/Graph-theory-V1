#ifndef SHORTEST_PATH_21_DIAJKSTRAS
#define SHORTEST_PATH_21_DIAJKSTRAS

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

class simple_graph {

	std::vector<vertex*> vertex_list;
	std::list<vertex*> processed_list;

	bool ADD_TO_PROCESSED_LIST = false;

	friend void DFS(simple_graph&, int);

	friend void sortest_path_dijkstras(simple_graph& , int );

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

void sortest_path_dijkstras(simple_graph& graph, int source_vertex_id)
{
	vertex * v1 = NULL;
	v1 = graph.initialize_and_find_vertex(source_vertex_id);
	
	//T represent the already sortest path determind set
	std::vector<vertex*> T;
	
	bool * state_array = new bool[graph.vertex_list.size()];
	//initialize state array 
	for (int i=0; i < graph.vertex_list.size(); i++)
	{
		state_array[i] = false;
	}

	//priority object
	class prioritize 
	{ 
		public: bool operator ()(std::pair<vertex*, int>&p1, std::pair<vertex*, int>p2)
		{ 
			return p1.second > p2.second; 
		} 
	};

	//min priority queue
	std::priority_queue<std::pair<vertex*,int>, std::vector<std::pair<vertex*, int>>,
		prioritize> pq;


	if (v1 == NULL)
	{
		throw std::runtime_error("dijkstras failed : cannot find source vertex with id - " + std::to_string(source_vertex_id));
	}
	else
	{
		//push source vertex to pq at the beginning.
		pq.push(std::make_pair(v1,v1->distance));
		
		while (!pq.empty())
		{
			vertex* u = NULL;
			int vertex_count = 0;
			bool found_in_current_iter = false;

			//check wether the virtex is already popped one
			while (!pq.empty())
			{
				u = pq.top().first;
				pq.pop();
				if (!state_array[u->node_id-1])
				{
					state_array[u->node_id-1] = true;
					found_in_current_iter = true;
					vertex_count++;
					break;
				}
			}

			if (!found_in_current_iter && vertex_count== graph.vertex_list.size())
				break;
			//end of check

			//add u to already sortest path determined list
			T.push_back(u);

			for each (auto v in u->adj_list)
			{
				if (!state_array[v.first->node_id-1] &&
					(v.first->distance > u->distance + v.second))
				{
					v.first->distance = u->distance + v.second;
					v.first->predecessor = u;
					pq.push(std::make_pair(v.first, v.first->distance));
				}
			}
		}
	}
}

#endif
