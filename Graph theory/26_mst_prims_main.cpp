//#include "26_mst_prims.h"
//#include <iostream>
//#include <string>
//
//int main() {
//	std::cout << "This is the example related to Video 25 - mst prims" 
//		<< std::endl;
//
//	simple_graph graph;
//
//	graph.add_node(1, "a");
//	graph.add_node(2, "b");
//	graph.add_node(3, "c");
//	graph.add_node(4, "d");
//	graph.add_node(5, "e");
//	graph.add_node(6, "f");
//	graph.add_node(7, "g");
//	graph.add_node(8, "h");
//	graph.add_node(9, "i");
//
//	graph.add_edge(1, 2, 4);
//	graph.add_edge(1, 8, 8);
//	graph.add_edge(2, 8, 11);
//	graph.add_edge(2, 3, 8);
//	graph.add_edge(3, 4, 7);
//	graph.add_edge(3, 9, 2);
//	graph.add_edge(3, 6, 4);
//	graph.add_edge(4, 6, 14);
//	graph.add_edge(4, 5, 9);
//	graph.add_edge(5, 6, 10);
//	graph.add_edge(6, 7, 2);
//	graph.add_edge(7, 8, 1);
//	graph.add_edge(8, 9, 7);
//
//	graph.add_edge(2, 1, 4);
//	graph.add_edge(8, 1, 8);
//	graph.add_edge(8, 2, 11);
//	graph.add_edge(3, 2, 8);
//	graph.add_edge(4, 3, 7);
//	graph.add_edge(9, 3, 2);
//	graph.add_edge(6, 3, 4);
//	graph.add_edge(6, 4, 14);
//	graph.add_edge(5, 4, 9);
//	graph.add_edge(6, 5, 10);
//	graph.add_edge(7, 6, 2);
//	graph.add_edge(8, 7, 1);
//	graph.add_edge(9, 8, 7);
//
//	mst_prims(graph,1);
//
//	std::cout << "mst kruskals ends" << std::endl;
//	system("pause");
//}