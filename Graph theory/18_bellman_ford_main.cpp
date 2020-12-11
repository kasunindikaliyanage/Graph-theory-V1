//#include "18_shortest_path_bellman_ford.h"
//#include <iostream>
//#include <string>
//
//int main(){
//	std::cout << "This is the example related to Video 18 - Bellman ford implementation" << std::endl;
//	
//	simple_graph graph;
//	graph.add_node(1, "s");
//	graph.add_node(2, "t");
//	graph.add_node(3, "x");
//	graph.add_node(4, "y");
//	graph.add_node(5, "z");
//
//	graph.add_edge(1, 2, 6);
//	graph.add_edge(1, 4, 7);
//	graph.add_edge(2, 3, 5);
//	graph.add_edge(2, 4, 8);
//	graph.add_edge(2, 5, -4);
//	graph.add_edge(3, 2, -2);
//	graph.add_edge(4, 3, -3);
//	graph.add_edge(4, 5, 9);
//	graph.add_edge(5, 1, 2);
//	graph.add_edge(5, 3, 7);
//
//	sortest_path_bellman_ford(graph, 1);
//
//	std::cout << "Bellman ford algorithm ends" << std::endl;
//	graph.print_nodes();
//	system("pause");
//}