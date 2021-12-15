//
// Created by mateu on 06.03.2021.
//

#ifndef OPT_GRAPH_H
#define OPT_GRAPH_H
#include <vector>
#include <unordered_set>
#include <tuple>
#include <memory>
#include <algorithm>
#include <variant>
#include <forward_list>
#include <cassert>

namespace graph {
    template<typename E>
    class Graph {
    private:
        int mVerticesNum;
        int mEdgesNum;
        std::vector<std::unordered_set<std::shared_ptr<E>>> mAdjList;
    public:
        Graph();
        explicit Graph(int verticesNum);
        Graph(int verticesNum, const std::vector<std::tuple<int, int, int>> &initializer);
        Graph(Graph<E> &graph) = default;
        Graph(Graph<E>&& moved) noexcept;
        void AddEdge(int f_vertex, int s_vertex, int weight);
        void AddEdge(std::shared_ptr<E> &edge);
        void DisconnectVertex(int vertexIndex);
        void RemoveEdge(const std::shared_ptr<E> &edge);
        [[nodiscard]] int EdgesNum() const;
        [[nodiscard]] int VerticesNum() const;
        [[nodiscard]] const std::vector<std::unordered_set<std::shared_ptr<E>>> &AdjList() const;
    };
}
template<typename E>
graph::Graph<E>::Graph() : graph::Graph<E>::Graph(0) {};

template<typename E>
graph::Graph<E>::Graph(int verticesNum) : mVerticesNum(verticesNum), mEdgesNum(0), mAdjList(verticesNum, std::unordered_set<std::shared_ptr<E>>()) {}

template<typename E>
graph::Graph<E>::Graph(int verticesNum, const std::vector<std::tuple<int, int, int>> &initializer) : Graph<E>(verticesNum) {
    for (auto &element : initializer) {
        AddEdge(std::get<0>(element), std::get<1>(element), std::get<2>(element));
    }
}

template<typename E>
graph::Graph<E>::Graph(Graph<E> &&moved) noexcept  : mVerticesNum(moved.mVerticesNum), mEdgesNum(moved.mEdgesNum), mAdjList(std::move(moved.mAdjList)) { };

template<typename E>
void graph::Graph<E>::AddEdge(int f_vertex, int s_vertex, int weight) {
    if (f_vertex < 0 || f_vertex >= mVerticesNum)
        throw std::out_of_range("f_vertex has invalid value");
    if (s_vertex < 0 || s_vertex >= mVerticesNum)
        throw std::out_of_range("s_vertex has invalid value");
    // edges is stored between vertices (adjList_). Lower vertex index is always first in internal edges representation.
    if (f_vertex > s_vertex)
        std::swap(f_vertex, s_vertex);
    // check if edge exists
    for (auto &edge : mAdjList[f_vertex])
        if (edge->vertexB == s_vertex)
            throw std::invalid_argument("Attempt to add edge for second time was made");
    auto edge = std::make_shared<E>(f_vertex, s_vertex, weight);
    mAdjList[f_vertex].insert(edge);
    mAdjList[s_vertex].insert(edge);
    mEdgesNum++;
}

template<typename E>
void graph::Graph<E>::AddEdge(std::shared_ptr<E> &edge) {
    assert(edge->vertexA >= 0 && edge->vertexB < mVerticesNum);
    for (auto &existingEdge : AdjList()[edge->vertexA]) {
        if(edge.get() == existingEdge.get())
            throw std::runtime_error("Edge added twice");
    }
    for (auto &existingEdge : AdjList()[edge->vertexB]) {
        if(edge.get() == existingEdge.get())
            throw std::runtime_error("Edge added twice");
    }
    mEdgesNum++;
    mAdjList[edge->vertexA].insert(edge);
    mAdjList[edge->vertexB].insert(edge);
}

template<typename E>
void graph::Graph<E>::DisconnectVertex(int vertexIndex) {
    for(auto &edge : mAdjList[vertexIndex]) {
        mAdjList[edge->Other(vertexIndex)].erase(edge);
        mEdgesNum--;
    }
    mAdjList[vertexIndex].clear();
}

template<typename E>
void graph::Graph<E>::RemoveEdge(const std::shared_ptr<E> &edge)  {
    mAdjList[edge->vertexB].erase(edge);
    mAdjList[edge->vertexA].erase(edge);
    mEdgesNum--;
}

template<typename E>
int graph::Graph<E>::EdgesNum() const {
    return mEdgesNum;
}

template<typename E>
int graph::Graph<E>::VerticesNum() const {
    return mVerticesNum;
}

template<typename E>
const std::vector<std::unordered_set<std::shared_ptr<E>>> &graph::Graph<E>::AdjList() const {
    return mAdjList;
}

namespace std {
    // std extension with hash function for graph edge
    using graph::Edge;
    using std::size_t;
    using std::hash;

    template<>
    struct hash<Edge> {
        size_t operator()(const Edge &edge) const {
            static_assert(std::is_same<decltype(Edge::vertexA), const int>::value,
                          "Edge hash function was created only for int types");
            static_assert(std::is_same<decltype(Edge::vertexB), const int>::value,
                          "Edge hash function was created only for int types");
            static_assert(std::is_same<decltype(Edge::weight), const int>::value,
                          "Edge hash function was created only for int types");
            // implementation based on https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
            // TODO: Test hash function
            return ((edge.vertexA ^ (edge.vertexB << 1)) >> 1) ^ (edge.weight << 1);
        }
    };
}
#endif //OPT_GRAPH_H
