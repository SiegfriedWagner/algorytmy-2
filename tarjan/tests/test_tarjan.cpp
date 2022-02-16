//
// Created by mateu on 16.02.2022.
//

#include "../tarjan.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../graph.h"

#define TestName TestTarjan

bool contains(const std::vector<CommonAncestor> &list, const CommonAncestor ancestor) {
    for (auto &from_list : list)
    {
        if (ancestor.first == from_list.first && ancestor.second == from_list.second)
            return true;
        if (ancestor.first == from_list.second && ancestor.second == from_list.first)
            return true;
    }
    return false;
}

TEST(TestName, Graph1) {
    Graph graph;
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(2, 5);
    Tarjan solver;
    auto solution = solver.solve(graph);
    ASSERT_TRUE(contains(solution, {4, 5, 2}));
    ASSERT_TRUE(contains(solution, {4, 3, 1}));
    ASSERT_TRUE(contains(solution, {2, 5, 1}));
}