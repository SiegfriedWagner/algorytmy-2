//
// Created by mateu on 23.01.2022.
//
// maximum flow algorithm with preflow
#include <iostream>
#include "./maximum_flow_preflow.h"

using namespace std;

int main(int argc, char **argv) {
    // matrix graph representation if network capacity maximum flow [from][to]
    MatrixGraph capacity(7);
    capacity.addEdge(0, 1, 7);
    capacity.addEdge(0, 3, 3);
    capacity.addEdge(1, 4, 6);
    capacity.addEdge(2, 0, 9);
    capacity.addEdge(2, 5, 9);
    capacity.addEdge(3, 6, 2);
    capacity.addEdge(3, 4, 9);
    capacity.addEdge(5, 3, 3);
    capacity.addEdge(5, 6, 6);
    capacity.addEdge(6, 4, 8);
    auto result = max_flow(capacity, 2, 4);
    // printVectorOfVectors(flow);
    cout << "max flow: " << result.first << endl;
}