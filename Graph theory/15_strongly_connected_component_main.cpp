//#include "15_strongly_connected components.h"
//#include <iostream>
//#include <string>
//
//int main() {
//	std::cout << "------This is the example related to Video 15 - strongly connected components-------" << std::endl;
//
//	simple_graph graph;
//
//	graph.add_node(1,"A");
//	graph.add_node(2,"B");
//	graph.add_node(3,"C");
//	graph.add_node(4,"D");
//	graph.add_node(5,"E");
//	graph.add_node(6,"F");
//	graph.add_node(7,"G");
//	graph.add_node(8,"H");
//
//
//	graph.add_edge(1, 2);
//
//	graph.add_edge(2, 3);
//	graph.add_edge(2, 5);
//	graph.add_edge(2, 6);
//
//	graph.add_edge(3, 4);
//	graph.add_edge(3, 7);
//
//	graph.add_edge(4, 3);
//	graph.add_edge(4, 8);
//
//	graph.add_edge(5, 1);
//	graph.add_edge(5, 6);
//
//	graph.add_edge(6, 7);
//
//	graph.add_edge(7, 8);
//	graph.add_edge(7, 6);
//
//	graph.add_edge(8, 8);
//	
//	strongly_connected_components(graph);
//
//	std::cout << "------------------strongly connected components ends------------------" << std::endl;
//	system("pause");
//}