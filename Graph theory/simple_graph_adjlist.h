//#ifndef SIMPLE_GRAPH_ADJLIST
//#define SIMPLE_GRAPH_ADJLIST
//
//#include <stdexcept>
//#include <string>
//#include <vector>
//#include <iostream>
//#include <stack>
//#include <queue>
//
//
//enum NODE_COLOR{
//	WHITE, GRAY, BLACK
//};
//
//struct vertex{
//	int node_id;
//	std::vector<std::pair<vertex*, int>> adj_list;
//	NODE_COLOR color = WHITE;
//	int distance = INT_MAX;
//	int predecessor_id = -1;
//
//	vertex(){}
//
//	vertex(int _id) :node_id(_id)
//	{}
//
//	void print_vertex()
//	{
//		std::cout << "Vertex id : " + std::to_string(node_id) + ", color : " + std::to_string(color)
//			+ ", distance :" + std::to_string(distance) + ", predecessor_id : " + std::to_string(predecessor_id) << std::endl;
//	}
//};
//
//class simple_graph_adjlist{
//
//	std::vector<vertex*> graph_vertex_list;
//
//	friend void DFS(simple_graph_adjlist&, int);
//	friend void BFS(simple_graph_adjlist&, int);
//	friend void shortest_path_dijkstra(simple_graph_adjlist&, int);
//	friend bool shortest_path_bellman_ford(simple_graph_adjlist&, int);
//	friend bool detect_cycle_with_dfs(simple_graph_adjlist&, int);
//	friend void union_find(simple_graph_adjlist&, int);
//
//public:
//	simple_graph_adjlist()
//	{}
//
//	~simple_graph_adjlist(){
//		for each (auto var in graph_vertex_list){
//			delete var;
//		}
//	}
//
//	void add_node(int _node_id){
//		for each (auto var in graph_vertex_list){
//			if (var->node_id == _node_id){
//				throw std::runtime_error("Failed adding node : node with node_id -" + std::to_string(_node_id) + " already exsits in graph");
//			}
//		}
//
//		graph_vertex_list.push_back(new vertex(_node_id));
//	}
//
//	void add_edge(int v1_id, int v2_id){
//		vertex * v1 = NULL;
//		vertex * v2 = NULL;
//
//		bool found_v1 = false;
//		bool found_v2 = false;
//
//		for each (auto var in graph_vertex_list){
//			if (var->node_id == v1_id){
//				v1 = var;
//				found_v1 = true;
//			}
//
//			if (var->node_id == v2_id){
//				v2 = var;
//				found_v2 = true;
//			}
//
//			if (found_v1 && found_v2)
//				break;
//		}
//
//		if (found_v1&& found_v2){
//			bool edge_already_exist = false;
//
//			for each(auto var in v1->adj_list){
//				if (var.first->node_id == v2_id){
//					edge_already_exist = true;
//					throw std::runtime_error("Failed adding edge : " + std::to_string(v1_id) + " - " + std::to_string(v2_id) + " edge already exsits");
//					break;
//				}
//			}
//			if (!edge_already_exist){
//				v1->adj_list.push_back(std::make_pair(v2, int(0)));
//			}
//
//		}
//		else{
//			throw std::runtime_error("Failed adding edge : one or both vertex does not exsits");
//		}
//	}
//
//	void print_graph(){
//		for each (auto vertex1 in graph_vertex_list){
//			for each(auto vertex2 in vertex1->adj_list){
//				std::cout << vertex1->node_id << " - " << vertex2.first->node_id << std::endl;
//			}
//		}
//	}
//
//	void print_nodes()
//	{
//		for each (auto var in graph_vertex_list){
//			var->print_vertex();
//		}
//	}
//};
//
//void DFS(simple_graph_adjlist& graph, int source_vertex_id)
//{
//	std::stack<vertex*> stk;
//	vertex * v1 = NULL;
//
//	for each (auto vertex1 in graph.graph_vertex_list)
//	{
//		vertex1->color = WHITE;
//		vertex1->distance = -1;
//		vertex1->predecessor_id = -1;
//
//		if (vertex1->node_id == source_vertex_id)
//			v1 = vertex1;
//	}
//
//	if (v1 == NULL)
//	{
//		throw std::runtime_error("BFS failed : cannot find source vertex with id - " + std::to_string(source_vertex_id));
//	}
//	else
//	{
//		stk.push(v1);
//		while (!stk.empty())
//		{
//			vertex* v_temp = stk.top();
//			stk.pop();
//			for each (auto var in v_temp->adj_list)
//			{
//				if (var.first->color == WHITE)
//				{
//					var.first->color = GRAY;
//					var.first->distance = v_temp->distance + 1;
//					var.first->predecessor_id = v_temp->node_id;
//					stk.push((vertex*)var.first);
//				}
//			}
//			v_temp->color = BLACK;
//		}
//	}
//}
//
//void BFS(simple_graph_adjlist& graph, int source_vertex_id)
//{
//	std::queue<vertex*> q;
//	vertex * v1 = NULL;
//
//	for each (auto vertex1 in graph.graph_vertex_list)
//	{
//		vertex1->color = WHITE;
//		vertex1->distance = -1;
//		vertex1->predecessor_id = -1;
//
//		if (vertex1->node_id == source_vertex_id)
//			v1 = vertex1;
//	}
//
//	if (v1 == NULL)
//	{
//		throw std::runtime_error("BFS failed : cannot find source vertex with id - " + std::to_string(source_vertex_id));
//	}
//	else
//	{
//		q.push(v1);
//		while (!q.empty())
//		{
//			vertex* v_temp = q.front();
//			q.pop();
//			for each (auto var in v_temp->adj_list)
//			{
//				if (var.first->color == WHITE)
//				{
//					var.first->color = GRAY;
//					var.first->distance = v_temp->distance + 1;
//					var.first->predecessor_id = v_temp->node_id;
//					q.push((vertex*)var.first);
//				}
//			}
//			v_temp->color = BLACK;
//		}
//	}
//}
//
//void shortest_path_dijkstra(simple_graph_adjlist& graph, int source_vertex_id)
//{
//	vertex * v1 = NULL;
//	auto compare_values = [](vertex* v1, vertex* v2){
//		return v1->distance > v2->distance;
//	};
//	std::priority_queue<vertex*, std::vector<vertex*>, decltype(compare_values)> pq;
//
//	for each (auto vertex1 in graph.graph_vertex_list)
//	{
//		vertex1->color = WHITE;
//		vertex1->distance = INT_MAX;
//		vertex1->predecessor_id = -1;
//
//		if (vertex1->node_id == source_vertex_id)
//		{
//			v1 = vertex1;
//		}
//
//		pq.push(vertex1);
//	}
//
//	if (v1 == NULL)
//	{
//		throw std::runtime_error("Sortest path: Dijkstra failed : cannot find source vertex with id - " + std::to_string(source_vertex_id));
//	}
//	else
//	{
//		v1->distance = 0;
//		while (!pq.empty())
//		{
//			vertex* v = pq.top();
//			pq.pop();
//			v->color = BLACK;
//			for each (auto u in v->adj_list)
//			{
//				if (u.first->color == WHITE && (u.first->distance > v->distance + u.second))
//				{
//					u.first->distance = v->distance + u.second;
//					u.first->predecessor_id = v->node_id;
//				}
//			}
//
//		}
//	}
//}
//
//bool shortest_path_bellman_ford(simple_graph_adjlist& graph, int source_vertex_id)
//{
//	vertex * v1 = NULL;
//	auto compare_values = [](vertex* v1, vertex* v2){
//		return v1->distance > v2->distance;
//	};
//
//	for each (auto vertex1 in graph.graph_vertex_list)
//	{
//		vertex1->color = WHITE;
//		vertex1->distance = INT_MAX;
//		vertex1->predecessor_id = -1;
//
//		if (vertex1->node_id == source_vertex_id)
//		{
//			v1 = vertex1;
//		}
//	}
//
//	if (v1 == NULL)
//	{
//		throw std::runtime_error("Sortest path: Dijkstra failed : cannot find source vertex with id - " + std::to_string(source_vertex_id));
//	}
//	else
//	{
//		v1->distance = 0;
//		int vertex_size = graph.graph_vertex_list.size();
//
//		//iterate |V|-1 time
//		for (int i = 0; i < vertex_size; i++)
//		{
//			//below is for going through all the edges
//			for each (auto v in graph.graph_vertex_list)
//			{
//				for each (auto e in v->adj_list)
//				{
//					if (v->distance != INT_MAX && e.first->distance < v->distance + e.second)
//					{
//						e.first->distance = v->distance + e.second;
//						e.first->predecessor_id = v->predecessor_id;
//					}
//				}
//			}
//		}
//
//
//		//below is for going through all the edges to find out negative cycles
//		for each (auto v in graph.graph_vertex_list)
//		{
//			for each (auto e in v->adj_list)
//			{
//				if (v->distance != INT_MAX && v->distance + e.second < e.first->distance)
//				{
//					std::cout << "Bellman ford algoritm : Graph contains negetive weight cycles";
//					return false;
//				}
//			}
//		}
//	}
//	return true;
//}
//
//bool detect_cycle_with_dfs(simple_graph_adjlist& graph, int source_vertex_id)
//{
//	std::stack<vertex*> stk;
//	vertex * v1 = NULL;
//
//	for each (auto vertex1 in graph.graph_vertex_list)
//	{
//		vertex1->color = WHITE;
//		vertex1->distance = -1;
//		vertex1->predecessor_id = -1;
//
//		if (vertex1->node_id == source_vertex_id)
//			v1 = vertex1;
//	}
//
//	if (v1 == NULL)
//	{
//		throw std::runtime_error("BFS failed : cannot find source vertex with id - " + std::to_string(source_vertex_id));
//	}
//	else
//	{
//		stk.push(v1);
//		while (!stk.empty())
//		{
//			vertex* v_temp = stk.top();
//			stk.pop();
//			for each (auto var in v_temp->adj_list)
//			{
//				if (var.first->color == WHITE)
//				{
//					var.first->color = GRAY;
//					var.first->distance = v_temp->distance + 1;
//					var.first->predecessor_id = v_temp->node_id;
//					stk.push((vertex*)var.first);
//				}
//				else if (var.first->color == GRAY)
//				{
//					return true;
//				}
//			}
//			v_temp->color = BLACK;
//		}
//	}
//	return false;
//}
//
//void union_find(simple_graph_adjlist&, int)
//{
//	
//}
//
//#endif