//#include "9_dfs.h"
//#include <iostream>
//#include <string>
//
//int main() {
//	std::cout << "This is the example related to Video 10 - DFS" << std::endl;
//
//	simple_graph graph;
//
//	graph.add_node(1, "A");
//	graph.add_node(2, "B");
//	graph.add_node(3, "C");
//	graph.add_node(4, "D");
//	graph.add_node(5, "E");
//	graph.add_node(6, "F");
//	graph.add_node(7, "G");
//	graph.add_node(8, "H");
//
//	graph.add_edge(1, 5);
//	graph.add_edge(2, 1);
//	graph.add_edge(2, 6);
//	graph.add_edge(4, 3);
//	graph.add_edge(4, 7);
//	graph.add_edge(4, 8);
//	graph.add_edge(5, 6);
//	graph.add_edge(6, 3);
//	graph.add_edge(6, 7);
//
//	DFS(graph,2);
//
//	graph.print_nodes();
//	system("pause");
//}