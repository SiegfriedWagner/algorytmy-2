//
// Created by mateu on 26.01.2022.
//

#include "../graph.h"
#include "tarjan.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    Graph graph;
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(2, 5);
    Tarjan tarjan;
    auto solution = tarjan.solve(graph);
    for (auto &ancestor : solution)
        cout << "Common ancestor of " << ancestor.first << " and " << ancestor.second << " is " << ancestor.common_ancestor << endl;
    return 0;
}