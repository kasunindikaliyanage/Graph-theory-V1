//#include "8_bfs.h"
//#include <iostream>
//#include <string>
//
//int main() {
//	std::cout << "This is the example related to Video 8 - BFS" << std::endl;
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
//	//edges of A
//	graph.add_edge(1, 2);
//	graph.add_edge(1, 5);
//
//	//edges of B
//	graph.add_edge(2, 1);
//	graph.add_edge(2, 6);
//
//	//edges of C
//	graph.add_edge(3, 6);
//	graph.add_edge(3, 7);
//	graph.add_edge(3, 4);
//
//	//edges of D
//	graph.add_edge(4, 3);
//	graph.add_edge(4, 7);
//	graph.add_edge(4, 8);
//
//	//edges of E
//	graph.add_edge(5, 1);
//	graph.add_edge(5, 6);
//
//	//edges of F
//	graph.add_edge(6, 2);
//	graph.add_edge(6, 3);
//	graph.add_edge(6, 7);
//
//	//edges of G
//	graph.add_edge(7, 3);
//	graph.add_edge(7, 4);
//	graph.add_edge(7, 8);
//	graph.add_edge(7, 6);
//
//	//edges of H
//	graph.add_edge(8,4);
//	graph.add_edge(8,7);
//	
//	BFS(graph, 2);
//
//	graph.print_nodes();
//	system("pause");
//}