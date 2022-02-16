//
// Created by mateu on 31.01.2022.
//

#include <iostream>
#include "./maximum_flow.h"
using namespace std;



// Driver program to test above functions
int main()
{
    // Let us create a graph shown in the above example
    MatrixGraph graph(6);
    graph.addEdge(0, 1, 16);
    graph.addEdge(0, 2, 13);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 12);
    graph.addEdge(2, 1, 4);
    graph.addEdge(2, 4, 14);
    graph.addEdge(3, 2, 9);
    graph.addEdge(3, 5, 20);
    graph.addEdge(4, 3, 7);
    graph.addEdge(4, 5, 4);
    auto result = fordFulkerson(graph, 0, 5);
    cout << "The maximum possible flow is " << result.first << endl;
    return 0;
}