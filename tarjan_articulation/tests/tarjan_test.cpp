//
// Created by mateu on 22.01.2022.
//

#include "../tarjan.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace std;
using namespace tarjan_articulation;

bool contains(vector<int> &vertices, int vertex) {
    for(auto e : vertices) {
        if (e == vertex)
            return true;
    }
    return false;
}
#define TestTarjan TestTarjanArticulation
TEST(TestTarjan, TestGraph1) {
    BiGraph graph;
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);
    auto solution = tarjan(graph);
    ASSERT_EQ(2, solution.size());
    ASSERT_TRUE(contains(solution, 0));
    ASSERT_TRUE(contains(solution, 3));
}

TEST(TestTrajan, TestGraph2) {
    BiGraph graph;
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(0,5);
    graph.addEdge(1, 4);
    graph.addEdge(1, 5);
    graph.addEdge(2,3);
    graph.addEdge(3, 6);
    graph.addEdge(3,7);
    graph.addEdge(4, 5);
    graph.addEdge(6, 7);
    auto solution = tarjan(graph);
    ASSERT_EQ(2, solution.size());
    ASSERT_TRUE(contains(solution, 0));
    ASSERT_TRUE(contains(solution, 3));
}