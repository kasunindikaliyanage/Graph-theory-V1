#ifndef MAXFLOW_FORD_FULKERSON_15
#define MAXFLOW_FORD_FULKERSON_15

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>


enum NODE_COLOR {
	WHITE, GRAY, BLACK
};

struct vertex {

	int node_id;
	std::string value;
	std::vector<std::pair<vertex*, int>> adj_list;

	NODE_COLOR color = WHITE;
	int distance = INT_MAX;
	vertex* parent = NULL;

	vertex() {}

	vertex(int _id, std::string _value = "") :node_id(_id), value(_value)
	{}

	void print_vertex()
	{
		std::cout << "Vertex id : " + std::to_string(node_id) + ", color : " + std::to_string(color)
			+ ", distance :" + std::to_string(distance) << std::endl;
	}
};

class simple_graph {

	std::vector<vertex*> graph_vertex_list;
	int access_counter = 0;

	friend void max_flow_ford_fulkerson(simple_graph_adjlist&, int, int);

	bool BFS(std::vector<vertex*> residual_graph, vertex* source, vertex* sink)
	{
		std::queue<vertex*> q;

		for each (auto var in residual_graph)
		{
			var->color = WHITE;
		}

		q.push(source);
		while (!q.empty())
		{
			vertex* v_temp = q.front();
			q.pop();
			for each (auto var in v_temp->adj_list)
			{
				if (var.first->color == WHITE &&  var.second != 0)
				{
					q.push((vertex*)var.first);
					var.first->color = GRAY;
					var.first->distance = v_temp->distance + 1;
					var.first->print_vertex = v_temp;

				}
			}
			v_temp->color = BLACK;
		}

		if (sink->color == WHITE)
			return false;
		return true;
	}

public:
	simple_graph()
	{}

	~simple_graph() {
		for each (auto var in graph_vertex_list) {
			delete var;
		}
	}

	void add_node(int _node_id) {
		for each (auto var in graph_vertex_list) {
			if (var->node_id == _node_id) {
				throw std::runtime_error("Failed adding node : node with node_id -" + std::to_string(_node_id) + " already exsits in graph");
			}
		}

		graph_vertex_list.push_back(new vertex(_node_id));
	}

	void add_edge(int v1_id, int v2_id, int weight = 0) {
		vertex * v1 = NULL;
		vertex * v2 = NULL;

		bool found_v1 = false;
		bool found_v2 = false;

		for each (auto var in graph_vertex_list) {
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
		for each (auto vertex1 in graph_vertex_list) {
			for each(auto vertex2 in vertex1->adj_list) {
				std::cout << vertex1->node_id << " - " << vertex2.first->node_id << std::endl;
			}
		}
	}

	void print_nodes()
	{
		for each (auto var in graph_vertex_list) {
			var->print_vertex();
		}
	}
};



void max_flow_ford_fulkerson(simple_graph& graph, int s, int t)
{
	std::vector<vertex*> residual_graph;

	//preparing residual network
	for each (auto var in graph.graph_vertex_list)
	{
		residual_graph.push_back(new vertex(var->node_id, var->value));
	}

	for each (auto var in graph.graph_vertex_list)
	{
		for each (auto var2 in var->adj_list)
		{
			int v1_id = var->node_id;
			int v2_id = var2.first->node_id;

			int weight = var2.second;
			vertex * residual_v1 = NULL;
			vertex * residual_v2 = NULL;

			bool found_v1 = false;
			bool found_v2 = false;

			for each (auto var in residual_graph) {
				if (var->node_id == v1_id) {
					residual_v1 = var;
					found_v1 = true;
				}

				if (var->node_id == v2_id) {
					residual_v2 = var;
					found_v2 = true;
				}

				if (found_v1 && found_v2)
					break;
			}

			if (found_v1 && found_v2)
			{
				residual_v1->adj_list.push_back(std::make_pair(residual_v2, weight));
				residual_v2->adj_list.push_back(std::make_pair(residual_v1, 0));
			}
		}
	}
	//end of preparing residual network

	vertex * source = NULL;
	vertex * sink = NULL;

	bool found_source = false;
	bool found_sink = false;

	for each (auto var in residual_graph) {
		if (var->node_id == s) {
			source = var;
			found_source = true;
		}

		if (var->node_id == t) {
			sink = var;
			found_sink = true;
		}

		var->parent = NULL;
	}

	if (found_source&& found_sink) {
		int max_flow = 0;
		vertex* u;
		while (graph.BFS(residual_graph,source,sink))
		{
			int path_flow = INT_MAX;
			for (vertex* v = sink; v != source; v = v->parent)
			{
				u = v->parent;
				
				for each (auto var in u->adj_list)
				{
					if (var.first->node_id == v->node_id)
					{
						path_flow = std::min(path_flow, var.second);
					}
				}
			}

			for (vertex* v = sink; v != source; v = v->parent)
			{
				u = v->parent;

				//set the forwards edge in residual network
				for each (auto var in u->adj_list)
				{
					if (var.first->node_id == v->node_id)
					{
						var.second -= path_flow;
					}
				}

				//set the back edge in residual network
				for each (auto var in v->adj_list)
				{
					if (var.first->node_id == u->node_id)
					{
						var.second += path_flow;
					}
				}
			}

			max_flow += path_flow;
		}
	}
	else {
		throw std::runtime_error("Failed adding edge : one or both vertex does not exsits");
	}
}

#endif