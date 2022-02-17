//
// Created by mateu on 31.01.2022.
//

#ifndef ALGORYTMY_2_MAXIMUM_FLOW_H
#define ALGORYTMY_2_MAXIMUM_FLOW_H
#include "../matrix_graph.h"
#include <climits>
#include <queue>
#include <utility>

bool bfs(const MatrixGraph & residualGraph, int s, int t, std::vector<int> &parent)
{
    std::vector<bool> visited(residualGraph.getVertexCount(), false);
    std::queue<int> queue;
    queue.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();

        for (int v = 0; v < residualGraph.getVertexCount(); v++) {
            if (!visited[v] && residualGraph.getEdges()[u][v] > 0) {
                if (v == t) {
                    // connection to sink node, end of bfs
                    parent[v] = u;
                    return true;
                }
                queue.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

// Returns the maximum flow from s to t in the given graph
std::pair<int, MatrixGraph> fordFulkerson(const MatrixGraph &graph, int source, int target)
{
    MatrixGraph resultGraph(graph.getVertexCount());
    int u, v;
    // innit residual graph with max capacity
    MatrixGraph residualgraph(graph.getVertexCount());
    for (u = 0; u < graph.getVertexCount(); u++)
        for (v = 0; v < graph.getVertexCount(); v++) {
            residualgraph.getEdges()[u][v] = graph.getEdges()[u][v];
        }
    // store for augmenting path
    std::vector<int> parent(graph.getVertexCount(), -1);

    int max_flow = 0; // There is no flow initially

    // while agumenting path
    while (bfs(residualgraph, source, target, parent)) {
        int path_flow = INT_MAX;
        for (int to = target; to != source; to = parent[to]) {
            int from = parent[to];
            path_flow = std::min(path_flow, residualgraph.getEdges()[from][to]);
        }

        // change flow
        for (int to = target; to != source; to = parent[to]) {
            int from = parent[to];
            residualgraph.getEdges()[from][to] -= path_flow;
            residualgraph.getEdges()[to][from] += path_flow;
            resultGraph.getEdges()[from][to] += path_flow;
        }
        max_flow += path_flow;
    }
    return {max_flow, resultGraph};
}
#endif //ALGORYTMY_2_MAXIMUM_FLOW_H
