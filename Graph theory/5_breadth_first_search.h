#ifndef SIMPLE_GRAPH_ADJLIST_5_H
#define SIMPLE_GRAPH_ADJLIST_5_H

#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <queue>

enum NODE_COLOR{
	WHITE, GRAY, BLACK
};

struct vertex{
	int vertex_id;
	std::vector<vertex*> adj_list;
	NODE_COLOR color = WHITE;

	int distance = INT_MAX;
	int predecessor_id = -1;

	vertex(){}

	vertex(int _id) :vertex_id(_id)
	{}

	void print_vertex()
	{
		std::cout << "Vertex id : " + std::to_string(vertex_id) + ", color : " + std::to_string(color)
			+ ", distance :" + std::to_string(distance) + ", predecessor_id : " + std::to_string(predecessor_id) << std::endl;
	}
};

class simple_graph{

	std::vector<vertex*> graph_vertex_list;

	friend void DFS(simple_graph&, int);
	friend void BFS(simple_graph&, int);

public:
	void add_node(int _node_id){
		for each (auto var in graph_vertex_list){
			if (var->vertex_id == _node_id){
				throw std::runtime_error("Failed adding node : node with node_id -" + std::to_string(_node_id) + " already exsits in graph");
			}
		}

		graph_vertex_list.push_back(new vertex(_node_id));
	}

	void add_edge(int v1_id, int v2_id){
		vertex * v1 = NULL;
		vertex * v2 = NULL;

		bool found_v1 = false;
		bool found_v2 = false;

		for each (auto var in graph_vertex_list){
			if (var->vertex_id == v1_id){
				v1 = var;
				found_v1 = true;
			}

			if (var->vertex_id == v2_id){
				v2 = var;
				found_v2 = true;
			}

			if (found_v1 && found_v2)
				break;
		}

		if (found_v1&& found_v2){
			bool edge_already_exist = false;

			for each(auto var in v1->adj_list){
				if (var->vertex_id == v2_id){
					edge_already_exist = true;
					throw std::runtime_error("Failed adding edge : " + std::to_string(v1_id) + " - " + std::to_string(v2_id) + " edge already exsits");
					break;
				}
			}
			if (!edge_already_exist){
				v1->adj_list.push_back(v2);
			}

		}
		else{
			throw std::runtime_error("Failed adding edge : one or both vertex does not exsits");
		}
	}

	void print_graph(){
		for each (auto vertex1 in graph_vertex_list){
			for each(auto vertex2 in vertex1->adj_list){
				std::cout << vertex1->vertex_id << " - " << vertex2->vertex_id << std::endl;
			}
		}
	}
};

void DFS(simple_graph & graph, int source_vertex_id)
{
	std::stack<vertex*> stk;
	vertex * v1 = NULL;

	for each (auto vertex1 in graph.graph_vertex_list)
	{
		vertex1->color = WHITE;
		vertex1->distance = -1;
		vertex1->predecessor_id = -1;

		if (vertex1->vertex_id == source_vertex_id)
			v1 = vertex1;
	}

	if (v1 == NULL)
	{
		throw std::runtime_error("BFS failed : cannot find source vertex with id - " + std::to_string(source_vertex_id));
	}
	else
	{
		stk.push(v1);
		while (!stk.empty())
		{
			vertex* v_temp = stk.top();
			stk.pop();
			for each (auto var in v_temp->adj_list)
			{
				if (var->color == WHITE)
				{
					var->color = GRAY;
					var->distance = v_temp->distance + 1;
					var->predecessor_id = v_temp->vertex_id;
					stk.push(var);
				}
			}
			v_temp->color = BLACK;
		}
	}
}

void BFS(simple_graph& graph, int source_vertex_id)
{
	std::queue<vertex*> q;
	vertex * v1 = NULL;

	for each (auto vertex1 in graph.graph_vertex_list)
	{
		vertex1->color = WHITE;
		vertex1->distance = -1;
		vertex1->predecessor_id = -1;

		if (vertex1->vertex_id == source_vertex_id)
			v1 = vertex1;
	}

	if (v1 == NULL)
	{
		throw std::runtime_error("BFS failed : cannot find source vertex with id - " + std::to_string(source_vertex_id));
	}
	else
	{
		q.push(v1);
		while (!q.empty())
		{
			vertex* v_temp = q.front();
			q.pop();
			for each (auto var in v_temp->adj_list)
			{
				if (var->color == WHITE)
				{
					var->color = GRAY;
					var->distance = v_temp->distance + 1;
					var->predecessor_id = v_temp->vertex_id;
					q.push(var);
				}
			}
			v_temp->color = BLACK;
		}
	}
}


#endif