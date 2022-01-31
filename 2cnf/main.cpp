//
// Created by Mateusz Chojnowski on 13.01.2022.
//

#include <vector>
#include <iostream>
#include "cnf_solver.h"

using namespace std;

int main(int arc, char **argv) {
    vector<int> right = {1, -2, -1, 3, -3, -4, -3};
    vector<int> left =  {2,  3, -2, 4, 5, -5, 4};

    CNF2Solver solver(getNumberOfTermsHelper(left, right));
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