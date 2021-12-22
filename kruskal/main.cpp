//
// Created by mateu on 09.12.2021.
//
#include "./edge.h"
#include "../external/argparse.h"
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <fstream>
#include <unordered_set>

using namespace std;
struct Subset {
    int rank;
    list<Edge<int, int>> elements;
};

void
subsets_union(const shared_ptr<Subset> from, const shared_ptr<Subset> to, vector<shared_ptr<Subset>> global_list) {
    for (auto &edge: from->elements) {
        global_list[edge.vertexA] = to;
        global_list[edge.vertexB] = to;
    }
    to->rank += from->rank;
    to->elements.splice(to->elements.begin(), from->elements);
}

int main(int arc, char **argv) {
    argparse::ArgumentParser parser("kruskal");
    parser.add_argument("input_file")
        .help("Input file with graph")
        .action([](const string &path) {
            fstream inputFile;
            inputFile.open(path.c_str(), fstream::in);
            int maxVertex = -1;
            int v1, v2, weight;
            vector<Edge<int, int>> edges;
            unordered_set<int> vertices;
            while (!inputFile.eof()) {
                inputFile >> v1;
                inputFile >> v2;
                inputFile >> weight;
                if (v1 > maxVertex)
                    maxVertex = v1;
                if (v2 > maxVertex)
                    maxVertex = v2;
                edges.emplace_back(v1, v2, weight);
                vertices.insert(v1);
                vertices.insert(v2);
            }
            sort(edges.begin(), edges.end(), [](Edge<int, int> &e1, Edge<int, int> &e2) {
                return e1.weight < e2.weight;
            });
            for (auto &edge: edges) {
                cout << edge.weight << " " << edge.vertexA << " " << edge.vertexB << endl;
            }
            vector<shared_ptr<Subset>> vertexToSubSet(maxVertex + 1, nullptr);
            auto edge = edges.begin();
            while (edge != edges.end()) {
                int from_index = edge->vertexA;
                int to_index = edge->vertexB;
                int from_rank =
                        vertexToSubSet[from_index] != nullptr ? vertexToSubSet[from_index]->rank : -1;
                int to_rank = vertexToSubSet[to_index] != nullptr ? vertexToSubSet[to_index]->rank : -2;
                if (from_rank < to_rank) {
                    swap(from_rank, to_rank);
                    swap(from_index, to_index);
                }
                if (to_rank < 0) {
                    vertexToSubSet[to_index] = make_shared<Subset>();
                    vertexToSubSet[to_index]->rank = 0;
                }
                vertexToSubSet[to_index]->elements.push_front(*edge);
                vertexToSubSet[to_index]->rank++;
                if (to_rank > 0)
                    subsets_union(vertexToSubSet[from_index], vertexToSubSet[to_index], vertexToSubSet);
                if (vertexToSubSet[to_index]->rank == vertices.size() - 1)
                    break;
                edge++;
            }
            for(auto &e :  vertexToSubSet[edge->vertexA]->elements) {
                cout << e.vertexA << " >-- " << e.weight << " --> " << e.vertexB << endl;
            }
        });
    parser.parse_args(arc, argv);
    return 0;
}