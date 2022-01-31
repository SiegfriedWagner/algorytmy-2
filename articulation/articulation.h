//
// Created by mateu on 22.01.2022.
//

#ifndef ALGORYTMY_2_ARTICULATION_H
#define ALGORYTMY_2_ARTICULATION_H

#include <vector>
#include <cassert>
#include "../bigraph.h"

namespace articulation {
    const int NOT_VISITED_VALUE = -1;

    int dfs(const BiGraph &graph, std::vector<int> &visited,
            std::vector<int> &articulation_points, const int vertex, const int from_vertex,
            int &last_visited_number) {
        assert(vertex < visited.size());
        assert(visited[vertex] == NOT_VISITED_VALUE);
        int low = visited[vertex] = ++last_visited_number;
        bool has_child_without_access_to_older = false;
        for (auto nextVertex: graph.getEdges()[vertex]) {
            if (nextVertex != from_vertex) {
                if (visited[nextVertex] == NOT_VISITED_VALUE) {
                    auto childLow= dfs(graph, visited, articulation_points, nextVertex, vertex, last_visited_number);
                    if (childLow < low)
                        low = childLow;
                    if (childLow >= visited[vertex])
                        has_child_without_access_to_older = true;
                }
                else if(visited[nextVertex] < low)
                    low = visited[nextVertex];
            }
        }
        if (has_child_without_access_to_older) {
            articulation_points.push_back(vertex);
        }

        return low;
    }

    std::vector<int> findArticulationPoints(const BiGraph &graph) {
        std::vector<int> result;
        std::vector<int> visited(graph.getVertexCount(), -1);
        // pick starting vertex index
        for (int vertex = 0; vertex < graph.getVertexCount(); ++vertex) {
            if (visited[vertex] != NOT_VISITED_VALUE || graph.getEdges()[vertex].empty()) {
                continue;
            }
            int childCount = 0;
            int last_visited_number = visited[vertex] = 1;
            for (int child_vertex : graph.getEdges()[vertex]) {
                if (visited[child_vertex] != NOT_VISITED_VALUE)
                    continue;
                childCount++;
                dfs(graph, visited, result, child_vertex, vertex, last_visited_number);
            }
            if (childCount > 1) {
                result.push_back(vertex);
            }
        }

        return result;
    }
}
#endif //ALGORYTMY_2_ARTICULATION_H
