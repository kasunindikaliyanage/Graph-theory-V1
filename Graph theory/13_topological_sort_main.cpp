//#include "13_topological_sort.h"
//#include <iostream>
//#include <string>
//
//int main() {
//	std::cout << "------This is the example related to Video 13 - topological sort-------" << std::endl;
//
//	simple_graph graph;
//
//	graph.add_node(1, "undershorts");
//	graph.add_node(2, "pants");
//	graph.add_node(3, "belt");
//	graph.add_node(4, "shirt");
//	graph.add_node(5, "tie");
//	graph.add_node(6, "jacket");
//	graph.add_node(7, "socks");
//	graph.add_node(8, "shoes");
//	graph.add_node(9, "watch");
//
//	graph.add_edge(1, 2);
//	graph.add_edge(1, 8);
//	graph.add_edge(2, 3);
//	graph.add_edge(2, 8);
//	graph.add_edge(3, 6);
//	graph.add_edge(4, 3);
//	graph.add_edge(4, 5);
//	graph.add_edge(5, 6);
//	graph.add_edge(7, 8);
//
//	topological_sort(graph,2);
//
//	std::cout << "------------------topological sort ends------------------" << std::endl;
//	system("pause");
//}