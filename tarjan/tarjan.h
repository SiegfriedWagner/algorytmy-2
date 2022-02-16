//
// Created by mateu on 16.02.2022.
//

#ifndef ALGORYTMY_2_TARJAN_H
#define ALGORYTMY_2_TARJAN_H
#include <vector>
#include "../graph.h"

struct CommonAncestor {
    const int first;
    const int second;
    const int common_ancestor;
    CommonAncestor(int first, int second, int common_ancestor) : first(first), second(second), common_ancestor(common_ancestor) { }
};

class Tarjan {
private:
    const int NO_VALUE = -1;
    std::vector<int> parent;
    std::vector<int> rank;
    std::vector<int> ancestor;
    std::vector<bool> finished;
    std::vector<CommonAncestor> commonAncestor;
    int setFind(int x) {
        if (parent[x] != x) {
            parent[x] = setFind(parent[x]);
        }
        return parent[x];
    }

    void setUnion(int x, int y) {
        int x_root = setFind(x);
        int y_root = setFind(y);
        if (rank[x_root] > rank[y_root])
            parent[y_root] = x_root;
        else if (rank[x_root] < rank[y_root])
            parent[x_root] = y_root;
        else {
            parent[y_root] = x_root;
            rank[x_root]++;
        }
    }
    void makeSet(int i) {
        parent[i] = i;
        rank[i] = 1;
    }
    void tarjanStep(int i, const Graph &graph) {
        makeSet(i);
        ancestor[i] = i;
        for(auto child : graph.getEdges()[i]) {
            tarjanStep(child, graph);
            setUnion(i, child);
            ancestor[setFind(i)] = i;
        }
        finished[i] = true;
        for (int j = 0; j < graph.getVertexCount(); ++j) {
            if (i != j && finished[j])
                commonAncestor.emplace_back(i, j, ancestor[setFind(j)]);
        }
    }
public:
    std::vector<CommonAncestor> solve(const Graph &graph) {
        parent.assign(graph.getVertexCount(), NO_VALUE);
        rank.assign(graph.getVertexCount(), NO_VALUE);
        ancestor.assign(graph.getVertexCount(), NO_VALUE);
        finished.assign(graph.getVertexCount(), false);
        for (int i = 0; i < graph.getVertexCount(); ++i) {
            if (parent[i] == NO_VALUE && !graph.getEdges()[i].empty()) {
                tarjanStep(i, graph);
            }
        }
        return std::move(commonAncestor);
    }
};
#endif //ALGORYTMY_2_TARJAN_H
