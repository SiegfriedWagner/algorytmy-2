//
// Created by mateu on 20.01.2022.
//

#include "../bridges.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace std;
using namespace bridges;
// https://eduinf.waw.pl/inf/alg/001_search/0130a.php#P2
bool contains(vector<Edge> &edges, Edge edge) {
    for(auto e : edges) {
        if (e.vertexA == edge.vertexA && e.vertexB == edge.vertexB || e.vertexA == edge.vertexB && e.vertexB == edge.vertexA)
            return true;
    }
    return false;
}
#define TestName TestBridges
TEST(TestName, TestGraph1) {
    BiGraph graph;
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 14);
    graph.addEdge(14, 13);
    graph.addEdge(14,16);
    graph.addEdge(13, 16);
    auto solution = findBridges(graph);
    ASSERT_EQ(2, solution.size());
    ASSERT_TRUE(contains(solution, Edge(1, 14)));
    ASSERT_TRUE(contains(solution, Edge(0, 3)));
}

TEST(TestName, TestGraph2) {
    BiGraph graph;
    graph.addEdge(9, 5);
    graph.addEdge(5, 6);
    graph.addEdge(6, 8);
    graph.addEdge(6, 7);
    auto solution = findBridges(graph);
    ASSERT_EQ(4, solution.size());
}

TEST(TestName, TestGraph3) {
    BiGraph graph;
    graph.addEdge(10, 15);
    graph.addEdge(15, 11);
    graph.addEdge(11, 4);
    graph.addEdge(4, 12);
    graph.addEdge(12, 15);
    auto solution = findBridges(graph);
    ASSERT_EQ(1, solution.size());
    ASSERT_TRUE(contains(solution, Edge(10, 15)));
}