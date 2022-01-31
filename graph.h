//
// Created by mateu on 26.01.2022.
//

#ifndef ALGORYTMY_2_GRAPH_H
#define ALGORYTMY_2_GRAPH_H

#include <vector>

class Graph {
    std::vector<std::vector<int>> edges_;
    int vertexCount_;
public :
    Graph() : vertexCount_(0), edges_() {}

    void addEdge(int from, int to) {
        int max = (from > to ? from : to) + 1;
        if (edges_.size() < max) {
            edges_.resize(max);
            vertexCount_ = max;
        }
        edges_[from].push_back(to);
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

#endif //ALGORYTMY_2_GRAPH_H

