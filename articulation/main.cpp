//
// Created by mateu on 21.01.2022.
//
#include "../bigraph.h"
#include "articulation.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv) {
    BiGraph graph;
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(0,5);
    graph.addEdge(1, 4);
    graph.addEdge(1, 5);
    graph.addEdge(2,3);
    graph.addEdge(3, 6);
    graph.addEdge(3,7);
    graph.addEdge(4, 5);
    graph.addEdge(6, 7);
    auto solution = articulation::findArticulationPoints(graph);
    for(auto vextex : solution) {
        cout << " " << vextex;
    }
    cout << endl;
}