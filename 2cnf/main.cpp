//
// Created by Mateusz Chojnowski on 13.01.2022.
//

#include <vector>
#include <cmath>
#include <cassert>
#include <stack>
#include <cstring>
#include <iostream>

using namespace std;
int getNegation(int value, int terms) {
    assert(value > 0);
    if (value > terms)
        return value - terms;
    return value + terms;
}
bool coloringAlgorithStep(vector<vector<int>> &implications, int currIndex, vector<int> &dyes, int color) {
    assert(currIndex > 0);
    int terms = implications.size() / 2;
    if (dyes[currIndex] == -color)
        return false;
    if (dyes[currIndex] == color)
        return true;
    int complementary = getNegation(currIndex, terms);
    dyes[currIndex] = color;
    dyes[complementary] = -color;
    for (int i = 0; i < implications[currIndex].size(); ++i) {
        if (!coloringAlgorithStep(implications, implications[currIndex][i], dyes, color)) {
            dyes[currIndex] = 0;
            dyes[complementary] = 0;
            return false;
        }
    }
    return true;
}
void coloringAlgorithm(vector<vector<int>> &implications, vector<int> &dyes) {
    for (int i = 1; i < implications.size(); ++i) {
        if (dyes[i] == 0)
        {
            if (!coloringAlgorithStep(implications, i, dyes, 1)) {
                assert(coloringAlgorithStep(implications, getNegation(i, implications.size() / 2), dyes, 1));
            }
        }
    }
}
class CNF2Solver {
private:
    vector<vector<int>> adjList;
    vector<vector<int>> adjInvList;
    const int terms;

    [[nodiscard]]
    int getNegation(int value) const {
        return ::getNegation(value, terms);
    }

    void firstDfs(int term, bool *visited, stack<int> &stk) {
        visited[term] = true;
        for (int next: adjList[term]) {
            if (!visited[next])
                firstDfs(next, visited, stk);
        }
        stk.push(term);
    }

    void secondDfs(int term, bool *visited, int *scc, int &counter) {
        visited[term] = true;

        for (int next: adjInvList[term]) {
            if (!visited[next])
                secondDfs(adjInvList[term][next], visited, scc, counter);
        }
        scc[term] = counter;
    }

public:
    CNF2Solver(int terms) : adjList(terms * 2 + 1), adjInvList(terms * 2 + 1), terms(terms) {};

    void addOrPair(int firstTerm, int secondTerm) {
        firstTerm = firstTerm > 0 ? firstTerm : terms - firstTerm;
        secondTerm = secondTerm > 0 ? secondTerm : terms - secondTerm;
        assert(firstTerm < terms * 2 + 1);
        assert(secondTerm < terms * 2 + 1);
        int negFirst = getNegation(firstTerm);
        int negSecond = getNegation(secondTerm);
        adjList[negFirst].push_back(secondTerm);
        adjInvList[secondTerm].push_back(negFirst);
        adjList[negSecond].push_back(firstTerm);
        adjInvList[firstTerm].push_back(negSecond);
    };

    vector<int> solve() {
        bool visited[terms * 2 + 1];
        memset(visited, false, sizeof visited);
        bool visitedInv[terms * 1];
        memset(visitedInv, false, sizeof visitedInv);
        int scc[terms * 2 + 1];
        memset(scc, 0, sizeof scc);
        int counter = 1;
        stack<int> stk;
        for (int i = 1; i < 2 * terms + 1; ++i)
            if (!visited[i])
                firstDfs(i, visited, stk);
        while (!stk.empty()) {
            auto top = stk.top();
            stk.pop();
            if (!visitedInv[top]) {
                secondDfs(top, visitedInv, scc, counter);
                counter++;
            }
        }
        for (int i = 1; i <= terms; i++) {
            // for any 2 variable x and -x lie in
            // same SCC
            if (scc[i] == scc[i + terms]) {
                return {};
            }
        }
        vector<int> dyes(2 * terms + 1, 0);
        coloringAlgorithm(adjList, dyes);
        dyes.resize(terms + 1);
        return dyes;
    }
};

int main(int arc, char **argv) {
    vector<int> right = // {1, -2, -1, 3, -3, -4, -3};
    {1, 1, 2, 2, 3, 1, 2, 3, 4, 5, 6 };
    vector<int> left =  // {2,  3, -2, 4, 5, -5, 4};
    {3, -4, -4, -5, -5, -6, -6, -6, 7, 7, 7};

    int maxTerm = 0;
    for (auto r: right) {
        auto abs_ = abs(r);
        maxTerm = maxTerm < abs_ ? abs_ : maxTerm;
    }
    for (auto l: left) {
        auto abs_ = abs(l);
        maxTerm = maxTerm < abs_ ? abs_ : maxTerm;
    }
    assert(right.size() == left.size());
    CNF2Solver solver(maxTerm);
    for (int i = 0; i < right.size(); ++i) {
        solver.addOrPair(right[i], left[i]);
    }
    auto solution = solver.solve();
    if (solution.empty())
        cout << "The given expression is unsatisfiable." << endl;
    else {
        cout << "The given expression is satisfiable." << endl;
        for (int i = 1; i < solution.size(); ++i) {
            if (solution[i] < 0)
                cout << "-";
            cout << "x" << i << " ";
        }
        cout << endl;
    }
    return 0;
}