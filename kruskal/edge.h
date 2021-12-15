//
// Created by mateu on 09.12.2021.
//

#ifndef ALGORYTMY_2_EDGE_H
#define ALGORYTMY_2_EDGE_H

#include <stdexcept>
template <typename VertexType=int, typename VertexWeightType=int>
struct Edge {
    VertexType vertexA;
    VertexType vertexB;
    VertexWeightType weight;
    Edge(VertexType f_vertex, VertexType s_vertex, VertexWeightType weight) : vertexA(f_vertex), vertexB(s_vertex), weight(weight) { }
    bool operator==(const Edge<VertexType, VertexWeightType> &other) const {
        return vertexA == other.vertexA && vertexB == other.vertexB && weight == other.weight;
    };
    [[nodiscard]] int Other(VertexType vertex) const {
        if (vertex == vertexA)
            return vertexB;
        else if (vertex == vertexB)
            return vertexA;
        else
            throw std::invalid_argument("Vertex id must be either to or v");
    };
};
#endif //ALGORYTMY_2_EDGE_H
