//
// Created by mateu on 27.01.2022.
//

#ifndef ALGORYTMY_2_MATRIX_GRAPH_H
#define ALGORYTMY_2_MATRIX_GRAPH_H

#include <vector>

class MatrixGraph {
    std::vector<std::vector<int>> edges_;
    int vertexCount_;
public :
    MatrixGraph() = delete;
    explicit MatrixGraph(int vertexCount) : vertexCount_(vertexCount), edges_(vertexCount, std::vector<int>(vertexCount, 0)) {}
    void addEdge(int from, int to, int weight) {
        if (from < 0 || from >= vertexCount_ || to < 0 || to >= vertexCount_ || edges_[from][to] != 0)
            return; // TODO: maybe throw exception
        edges_[from][to] = weight;
    }

    [[nodiscard]]
    int getVertexCount() const {
        return vertexCount_;
    };

    [[nodiscard]]
    const std::vector<std::vector<int>> &getEdges() const {
        return edges_;
    }
};

#endif //ALGORYTMY_2_MATRIX_GRAPH_H
