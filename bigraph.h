//
// Created by mateu on 21.01.2022.
//

#ifndef ALGORYTMY_2_BIGRAPH_H
#define ALGORYTMY_2_BIGRAPH_H
#include <vector>
struct Edge {
    const int vertexA;
    const int vertexB;

    Edge(int vertexA, int vertexB) : vertexA(vertexA), vertexB(vertexB) {

    }
};

class BiGraph {
private:
    std::vector<std::vector<int>> edges_; // [first][second]
    int vertexCount_;
public:
    BiGraph() : vertexCount_(0), edges_() {}

    void addEdge(int first, int second) {
        int max = (first > second ? first : second) + 1;
        if (edges_.size() < max) {
            edges_.resize(max);
            vertexCount_ = max;
        }
        edges_[first].push_back(second);
        edges_[second].push_back(first);
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

#endif //ALGORYTMY_2_BIGRAPH_H
