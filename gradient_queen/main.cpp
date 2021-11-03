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
                cout << "O ";
        }
        cout << endl;
    }
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
        numberOfConflicts = 0;
        shuffle(rows.begin(), rows.end(), std::mt19937(std::random_device()()));
        // zero conflict vector
        for (int i = 0; i < northEast.size(); ++i) {
            northEast[i] = 0;
            northWest[i] = 0;
        }
        for (uint_fast32_t row = 0; row < rows.size(); ++row) {
            auto col = rows[row];
            auto northWestIndex = col + rows.size() - row - 1;
            auto northEastIndex = col + row;
            if (++northWest[northWestIndex] > 1)
                numberOfConflicts+=2;
            if (++northEast[northEastIndex] > 1)
                numberOfConflicts+=2;
        }
        // cout << "Number of conflicts: " << numberOfConflicts << endl;
        uint_fast32_t swaps = 1;
        while (numberOfConflicts > 0 && swaps > 0) {
            swaps = 0;
            for (int icol = 0; icol < rows.size(); ++icol) {
                for (int jcol = icol + 1; jcol < rows.size(); ++jcol) {
                    auto conflictsCopy = numberOfConflicts;
                    auto irow = rows[icol];
                    auto inorthWestIndex = icol + rows.size() - irow - 1;
                    auto inorthEastIndex = icol + irow;
                    auto jrow = rows[jcol];
                    auto jnorthWestIndex = jcol + rows.size() - jrow - 1;
                    auto jnorthEastIndex = jcol + jrow;
                    auto inewNorthWestIndex = jcol + rows.size() - irow - 1;
                    auto inewNorthEastIndex = jcol + irow;
                    auto jnewNortWestIndex = icol + rows.size() - jrow - 1;
                    auto jnewNorthEastIndex = icol + jrow;
                    if (northWest[inorthWestIndex]-- > 1)
                        conflictsCopy--;
                    if (northEast[inorthEastIndex]-- > 1)
                        conflictsCopy--;
                    if (northWest[jnorthWestIndex]-- > 1)
                        conflictsCopy--;
                    if (northEast[jnorthEastIndex]-- > 1)
                        conflictsCopy--;
                    if (++northWest[inewNorthWestIndex] > 1)
                        conflictsCopy++;
                    if (++northEast[inewNorthEastIndex] > 1)
                        conflictsCopy++;
                    if (++northWest[jnewNortWestIndex] > 1)
                        conflictsCopy++;
                    if (++northEast[jnewNorthEastIndex] > 1)
                        conflictsCopy++;
                    // check conflicts number
                    if (conflictsCopy < numberOfConflicts) {
                        // accept change
                        swap(rows[icol], rows[jcol]);
                        // cout << "New conflicts :" << conflictsCopy << endl;
                        numberOfConflicts = conflictsCopy;
                        swaps++;
                    }
                    else {
                        // rollback
                        ++northWest[inorthWestIndex];
                        ++northEast[inorthEastIndex];
                        ++northWest[jnorthWestIndex];
                        ++northEast[jnorthEastIndex];
                        --northWest[inewNorthWestIndex];
                        --northEast[inewNorthEastIndex];
                        --northWest[jnewNortWestIndex];
                        --northEast[jnewNorthEastIndex];
                    }

                }
            }
            // cout << "Swaps: " << swaps << endl;
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