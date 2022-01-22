//
// Created by mateu on 22.01.2022.
//

#ifndef ALGORYTMY_2_TARJAN_H
#define ALGORYTMY_2_TARJAN_H

#include <vector>
#include <cassert>
#include "../bigraph.h"

namespace tarjan_articulation {
    const int NOT_VISITED_VALUE = -1;

    int tarjan_dfs(const BiGraph &graph, std::vector<int> &visited,
                    std::vector<int> &articulationPoints, const int vertex, const int fromVertex,
                    int &lastVisitedNumber) {
        assert(vertex < visited.size());
        assert(visited[vertex] == NOT_VISITED_VALUE);
        int low = visited[vertex] = ++lastVisitedNumber;
        bool test = false;
        for (auto nextVertex: graph.getEdges()[vertex]) {
            if (nextVertex != fromVertex) {
                if (visited[nextVertex] == NOT_VISITED_VALUE) {
                    auto childLow= tarjan_dfs(graph, visited, articulationPoints, nextVertex, vertex, lastVisitedNumber);
                    if (childLow < low)
                        low = childLow;
                    if (childLow >= visited[vertex])
                        test = true;
                }
                else if(visited[nextVertex] < low)
                    low = visited[nextVertex];
            }
        }
        if (test) {
            articulationPoints.push_back(vertex);
        }

        return low;
    }

    std::vector<int> tarjan(const BiGraph &graph) {
        std::vector<int> result;
        std::vector<int> visited(graph.getVertexCount(), -1);
        // pick starting vertex index
        for (int vertex = 0; vertex < graph.getVertexCount(); ++vertex) {
            if (visited[vertex] != NOT_VISITED_VALUE || graph.getEdges()[vertex].empty()) {
                continue;
            }
            int childCount = 0;
            int lastVisitedNumber = visited[vertex] = 1;
            for (int childVertex : graph.getEdges()[vertex]) {
                if (visited[childVertex] != NOT_VISITED_VALUE)
                    continue;
                childCount++;
                tarjan_dfs(graph, visited, result, childVertex, vertex, lastVisitedNumber);
            }
            if (childCount > 1) {
                result.push_back(vertex);
            }
        }

        return result;
    }
}
#endif //ALGORYTMY_2_TARJAN_H
