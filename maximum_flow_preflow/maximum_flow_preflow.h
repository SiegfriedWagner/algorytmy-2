//
// Created by mateu on 16.02.2022.
//

#ifndef ALGORYTMY_2_MAXIMUM_FLOW_PREFLOW_H
#define ALGORYTMY_2_MAXIMUM_FLOW_PREFLOW_H
#include <vector>
#include <queue>
#include <climits>
#include "../matrix_graph.h"

void push(int from, int to, std::vector<int> &excess, const MatrixGraph &capacity, MatrixGraph &flow, std::queue<int> &vertices_with_excess) {
    int pushedFlow = std::min(excess[from], capacity.getEdges()[from][to] - flow.getEdges()[from][to]);
    if (pushedFlow > 0) {
        flow.getEdges()[from][to] += pushedFlow;
        flow.getEdges()[to][from] -= pushedFlow;
        excess[from] -= pushedFlow;
        excess[to] += pushedFlow;
        if (excess[to] == pushedFlow) // check if excess is equal to pushed flow to avoid adding vertex twice
            vertices_with_excess.push(to);
    }
}

void relabel(int vertex, const MatrixGraph &capacity, MatrixGraph &flow, std::vector<int> &height)
{
    int d = INT_MAX;
    for (int i = 0; i < capacity.getVertexCount(); i++) {
        if (capacity.getEdges()[vertex][i] - flow.getEdges()[vertex][i] > 0)
            d = std::min(d, height[i]);
    }
    if (d < INT_MAX)
        height[vertex] = d + 1;
}

void discharge(const int from, std::vector<int> &excess, std::vector<int> &labels, const MatrixGraph &capacity, MatrixGraph &flow, std::vector<int> &height, std::queue<int> &vertices_with_excess) {
    while(excess[from] > 0) {
        if (labels[from] < labels.size()) {
            int to = labels[from];
            if (capacity.getEdges()[from][to] - flow.getEdges()[from][to] > 0 && height[from] > height[to])
                push(from, to, excess, capacity, flow, vertices_with_excess);
            else
                labels[from]++;
        }
        else {
            relabel(from, capacity, flow, height);
            labels[from] = 0;
        }
    }
}

std::pair<int, MatrixGraph> max_flow(const MatrixGraph &capacityGraph, const int source, const int target) {
    const int vertices = (int) capacityGraph.getVertexCount();
    MatrixGraph flow(capacityGraph.getVertexCount());
    std::vector<int> excess(vertices, 0);
    std::vector<int> height(vertices, 0);
    std::vector<int> labels(vertices, 0);
    std::queue<int> vertices_with_excess;
    height[source] = vertices; // source has top most height
    excess[source] = INT_MAX; // assume for now that source is infinite
    for (int child = 0; child < vertices; ++child) {
        if (child != source)
            push(source, child, excess, capacityGraph, flow, vertices_with_excess);
    }
    while(!vertices_with_excess.empty()) {
        int excess_vertex = vertices_with_excess.front();
        vertices_with_excess.pop();
        if (excess_vertex != source && excess_vertex != target)
            discharge(excess_vertex, excess, labels, capacityGraph, flow, height, vertices_with_excess);
    }
    int maxflow = 0;
    for (int i = 0; i < flow.getVertexCount(); ++i)
        maxflow += flow.getEdges()[i][target];
    return {maxflow, flow};
}

#endif //ALGORYTMY_2_MAXIMUM_FLOW_PREFLOW_H
