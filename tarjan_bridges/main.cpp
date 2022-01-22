//
// Created by mateu on 19.01.2022.
//
#include <iostream>
#include "tarjan.h"
using namespace std;
int main(int argc, char **argv) {
    // https://eduinf.waw.pl/inf/alg/001_search/0130a.php#P2
    BiGraph graph;
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    auto solution = tarjan_bridge::trajan(graph);
    for (auto bridge: solution)
        cout << bridge.vertexB << "  <-->  " << bridge.vertexA << endl;
    return 0;
}
