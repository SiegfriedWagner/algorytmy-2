#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

void printSolution(const vector<int> &rows) {
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

bool placeQueens(vector<bool> &northEast, vector<bool> &northWest, vector<bool> &occupiedRows, vector<int> &rows, int depth) {
    if (rows.size() == depth) {
        printSolution(rows);
        return true;
    }
    for (int row = 0; row < rows.size(); ++row) {
        int northWestIndex = depth - row + ((int) rows.size()) - 1;
        int northEastIndex = depth + row;
        assert(northWestIndex > 0 && northWestIndex < northWest.size());
        if (!northWest[northWestIndex] && !northEast[northEastIndex] && !occupiedRows[row]) {
            northWest[northWestIndex] = true;
            northEast[northEastIndex] = true;
            occupiedRows[row] = true;
            rows[depth] = row;
            if (placeQueens(northEast, northWest, occupiedRows, rows, depth + 1))
                return true;
            else {
                northWest[northWestIndex] = false;
                northEast[northEastIndex] = false;
                occupiedRows[row] = false;
                rows[depth] = -1;
            }
        }
    }
    return false;
}

void placeQueens(int chessboardSize) {
    vector<bool> northEast(chessboardSize * 2 - 1, false);
    vector<bool> northWest(chessboardSize * 2 - 1, false);
    vector<bool> occupiedRows(chessboardSize, false);
    vector<int> rows(chessboardSize, -1);
    placeQueens(northEast, northWest, occupiedRows, rows, 0);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Missig argument {chessboardSize:int}" << endl;
        return 1;
    }
    int chessBoardSize = stoi(string(argv[1]));
    placeQueens(chessBoardSize);
}
