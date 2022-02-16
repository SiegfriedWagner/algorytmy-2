//
// Created by mateu on 16.02.2022.
//

#include "../maximum_flow.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#define TestName TestMaximumFlow

TEST(TestName, Graph1) {
    MatrixGraph graph(6);
    graph.addEdge(0, 1, 16);
    graph.addEdge(0, 2, 13);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 12);
    graph.addEdge(2, 1, 4);
    graph.addEdge(2, 4, 14);
    graph.addEdge(3, 2, 9);
    graph.addEdge(3, 5, 20);
    graph.addEdge(4, 3, 7);
    graph.addEdge(4, 5, 4);
    auto result = fordFulkerson(graph, 0, 5);
    ASSERT_EQ(23, result.first);
}

TEST(TestName, Graph2) {
    MatrixGraph graph(6);
    graph.addEdge(0, 1, 6);
    graph.addEdge(0, 2, 3);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 4, 3);
    graph.addEdge(2, 4, 7);
    graph.addEdge(2, 5, 9);
    graph.addEdge(3, 2, 1);
    graph.addEdge(3, 5, 2);
    graph.addEdge(5, 4, 5);
    auto result = fordFulkerson(graph, 0, 4);
    ASSERT_EQ(10, result.first);
}

TEST(TestName, Graph3) {
    MatrixGraph capacity(7);
    capacity.addEdge(0, 1, 7);
    capacity.addEdge(0, 3, 3);
    capacity.addEdge(1, 4, 6);
    capacity.addEdge(2, 0, 9);
    capacity.addEdge(2, 5, 9);
    capacity.addEdge(3, 6, 2);
    capacity.addEdge(3, 4, 9);
    capacity.addEdge(5, 3, 3);
    capacity.addEdge(5, 6, 6);
    capacity.addEdge(6, 4, 8);
    auto result = fordFulkerson(capacity, 2, 4);
    ASSERT_EQ(18, result.first);
}

TEST(TestName, NoFlow) {
    MatrixGraph graph(2);
    graph.addEdge(0, 1, 10);
    auto result = fordFulkerson(graph, 1, 0);
    ASSERT_EQ(0, result.first);
}