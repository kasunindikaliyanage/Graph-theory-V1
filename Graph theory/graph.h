//#ifndef GRAPH_H
//#define GRAPH_H
//
//
//#include <stdexcept>
//#include <string>
//#include <vector>
//#include <iostream>
//#include <stack>
//#include <queue>
//
//
//class graph{
//
//
//	friend void DFS(simple_graph_adjlist&, int);
//	friend void BFS(simple_graph_adjlist&, int);
//	friend void shortest_path_dijkstra(simple_graph_adjlist&, int);
//	friend bool shortest_path_bellman_ford(simple_graph_adjlist&, int);
//
//protected:
//	enum NODE_COLOR{
//		WHITE, GRAY, BLACK
//	};
//
//	struct vertex{
//		int node_id;
//		std::vector<std::pair<vertex*, int>> adj_list;
//		NODE_COLOR color = WHITE;
//		int distance = INT_MAX;
//		int predecessor_id = -1;
//
//		vertex(int _id) :node_id(_id)
//		{}
//
//		void print_vertex()
//		{
//			std::cout << "Vertex id : " + std::to_string(node_id) + ", color : " + std::to_string(color)
//				+ ", distance :" + std::to_string(distance) + ", predecessor_id : " + std::to_string(predecessor_id) << std::endl;
//		}
//	};
//
//
//
//};
//#endif