//#include "19_shortest_path_in_dag.h"
//#include <iostream>
//#include <string>
//
//int main(){
//	std::cout << "This is the example related to Video 19 - shortest path in DAG implementation" << std::endl;
//	
//	simple_graph graph;
//	graph.add_node(1, "r");
//	graph.add_node(2, "s");
//	graph.add_node(3, "t");
//	graph.add_node(4, "x");
//	graph.add_node(5, "y");
//	graph.add_node(6, "z");
//
//	graph.add_edge(1, 2, 5);
//	graph.add_edge(2, 3, 2);
//	graph.add_edge(3, 4, 7);
//	graph.add_edge(4, 5, -1);
//	graph.add_edge(5, 6, -2);
//	graph.add_edge(1, 3, 3);
//	graph.add_edge(3, 5, 4);
//	graph.add_edge(3, 6, 2);
//	graph.add_edge(4, 6, 1);
//	graph.add_edge(2, 4, 6);
//
//	sortest_path_topological(graph, 2);
//	std::cout << std::endl;
//
//	graph.print_nodes();
//	system("pause");
//}