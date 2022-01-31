//
// Created by mateu on 27.01.2022.
//

#ifndef ALGORYTMY_2_CNF_SOLVER_H
#define ALGORYTMY_2_CNF_SOLVER_H
#include <cassert>
#include <vector>
#include <stack>
int getNumberOfTermsHelper(std::vector<int> &left, std::vector<int> &right) {
    if (left.size() != right.size())
        return -1;
    int maxTerm = 0;
    for (auto r: right) {
        auto abs_ = abs(r);
        maxTerm = maxTerm < abs_ ? abs_ : maxTerm;
    }
    for (auto l: left) {
        auto abs_ = abs(l);
        maxTerm = maxTerm < abs_ ? abs_ : maxTerm;
    }
    return maxTerm;
}

class CNF2Solver {
private:
    std::vector<std::vector<int>> adjList;
    std::vector<std::vector<int>> adjInvList;
    const int terms;

    [[nodiscard]]
    int getNegation(int value) const {
        assert(value > 0);
        if (value > terms)
            return value - terms;
        return value + terms;
    }

    void firstDfs(int term, std::vector<bool> &visited, std::stack<int> &stk) {
        assert(visited[term] == false);
        visited[term] = true;
        for (int next: adjList[term]) {
            if (!visited[next])
                firstDfs(next, visited, stk);
        }
        stk.push(term);
    }

    void secondDfs(int term, std::vector<bool> &visited, std::vector<int>  &scc, int &counter) {
        assert(visited[term] == false);
        visited[term] = true;

        for (int i = 1; i < adjInvList[term].size(); i++)
        {
            auto next = adjInvList[term][i];
            if (!visited[next])
                secondDfs(next, visited, scc, counter);
        }
        scc[term] = counter;
    }

public:
    CNF2Solver(int terms) : adjList(terms * 2 + 1), adjInvList(terms * 2 + 1), terms(terms) {
        assert(terms > 0);
    };

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

    std::vector<int> solve() {
        std::vector<bool> visited(terms * 2 + 1, false);
        visited[0] = true;
        std::vector<bool> visited_inv(terms * 2 + 1, false);
        visited_inv[0] = true;
        std::vector<int> scc(terms * 2 + 1, 0);
        int counter = 1;
        std::stack<int> stk;
        for (int i = 1; i < 2 * terms + 1; ++i)
            if (!visited[i])
                firstDfs(i, visited, stk);
        while (!stk.empty()) {
            auto top = stk.top();
            stk.pop();
            if (!visited_inv[top]) {
                secondDfs(top, visited_inv, scc, counter);
                counter++;
            }
        }
        std::vector<int> solution(terms + 1, 0);
        for (int i = 1; i <= terms; i++) {
            if (scc[i] == scc[getNegation(i)]) {
                return {};
            }
            solution[i] = scc[i] > scc[i + terms] ? 1 : -1;
        }
        return solution;
    }
};
#endif //ALGORYTMY_2_CNF_SOLVER_H
