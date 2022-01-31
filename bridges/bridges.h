//
// Created by mateu on 20.01.2022.
//

#ifndef ALGORYTMY_2_ARTICULATION_H
#define ALGORYTMY_2_TARJAN_H

#include <vector>
#include <climits>
#include <iostream>
#include <cassert>
#include "../bigraph.h"
#define NOT_VISITED_VALUE -1
namespace bridges {
// returns true if bridge exists between current and next edge
    bool
    dfs(const BiGraph &graph, std::vector<int> &visited, std::vector<int> &low, const int vertex, int &lastVisitedNumber,
        std::vector<Edge> &bridges, const int fromVertex) {
        assert(visited[vertex] == NOT_VISITED_VALUE);
        visited[vertex] = ++lastVisitedNumber;
        for (int newVertex: graph.getEdges()[vertex]) {
            if (visited[newVertex] != NOT_VISITED_VALUE) {
                if (newVertex != fromVertex) {
                    int min = visited[newVertex] < low[newVertex] ? visited[newVertex] : low[newVertex];
                    if (low[vertex] > min)
                        low[vertex] = min;
                }
                continue;
            } else if (dfs(graph, visited, low, newVertex, lastVisitedNumber, bridges, vertex)) {
                bridges.emplace_back(vertex, newVertex);
            }
        }
        int lowCalc = low[vertex] > visited[vertex] ? visited[vertex] : low[vertex];
        for (int neighbour: graph.getEdges()[vertex]) {
            if (neighbour == fromVertex)
                continue;
            if (low[neighbour] > 0 && low[neighbour] < lowCalc) {
                lowCalc = low[neighbour];
            }
        }
        low[vertex] = lowCalc;
        return lowCalc == visited[vertex];
    }

    std::vector<Edge> findBridges(const BiGraph &graph) {
        std::vector<Edge> result;
        int vertex = 0;
        // pick starting vertex index
        for (; vertex < graph.getVertexCount(); ++vertex)
            if (!graph.getEdges()[vertex].empty()) {
                break;
            }
        std::vector<int> low(graph.getVertexCount(), INT_MAX);
        std::vector<int> visited(graph.getVertexCount(), NOT_VISITED_VALUE);
        int lastVisitedNumber = 0;
        dfs(graph, visited, low, vertex, lastVisitedNumber, result, -1);
        return result;
    }
}
#endif //ALGORYTMY_2_ARTICULATION_H
