//
// Created by mateu on 02.11.2021.
//
#include <iostream>
#include <random>
#include <vector>
#include <cassert>

using namespace std;
void printSolution(const vector<uint_fast32_t> &rows) {
    for (int row: rows) {
        for (int col: rows) {
            if (rows[col] == row)
                cout << "H ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}

uint_fast32_t calculateConflicts(vector<uint_fast32_t> &northEast, vector<uint_fast32_t> &northWest, vector<uint_fast32_t> &rows) {
    uint_fast32_t numberOfConflicts = 0;
    for (int i = 0; i < northEast.size(); ++i) {
        northEast[i] = 0;
        northWest[i] = 0;
    }
    for (uint_fast32_t row = 0; row < rows.size(); ++row) {
        auto col = rows[row];
        auto northWestIndex = col + rows.size() - row - 1;
        auto northEastIndex = col + row;
        northWest[northWestIndex]++;
        northEast[northEastIndex]++;
    }
    for (int i = 0; i < northEast.size(); ++i) {
        if (northEast[i] > 0)
            numberOfConflicts += northEast[i] - 1;
        if (northWest[i] > 0)
            numberOfConflicts += northWest[i] - 1;
    }
    return numberOfConflicts;
}

vector<uint_fast32_t> placeQueens(uint_fast32_t chessboardSize) {
    vector<uint_fast32_t> northEast(chessboardSize * 2 - 1, 0);
    vector<uint_fast32_t> northWest(chessboardSize * 2 - 1, 0);
    vector<uint_fast32_t> rows(chessboardSize);
    for (uint_fast32_t i = 0; i < rows.size(); ++i)
        rows[i] = i;
    // mix initial positions
    uint_fast32_t numberOfConflicts = 1;
    while(numberOfConflicts > 0) {
        shuffle(rows.begin(), rows.end(), std::mt19937(std::random_device()()));
        numberOfConflicts = calculateConflicts(northEast, northWest, rows);
        uint_fast32_t swaps = 1;
        while (numberOfConflicts > 0 && swaps > 0) {
            swaps = 0;
            for (int icol = 0; icol < rows.size(); ++icol) {
                for (int jcol = icol + 1; jcol < rows.size(); ++jcol) {
                    swap(rows[icol], rows[jcol]);
                    auto newConflicts = calculateConflicts(northEast, northWest, rows);
                    // check conflicts number
                    if (newConflicts < numberOfConflicts) {
                        // accept change
                        numberOfConflicts = newConflicts;
                        swaps++;
                    }
                    else {
                        // rollback
                        swap(rows[icol], rows[jcol]);
                    }

                }
            }
        }
    }
    assert(numberOfConflicts == 0);
    return rows;
}

int main(int argc, char ** argv) {
    if (argc < 2) {
        cout << "Missig argument {chessboardSize:int}" << endl;
        return 1;
    }
    uint_fast32_t chessBoardSize = stoi(string(argv[1]));
    auto solution = placeQueens(chessBoardSize);
    printSolution(solution);
    return 0;
}