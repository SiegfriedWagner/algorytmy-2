#include <array>
#include <vector>
#include <cassert>
#include <tuple>
#include <iostream>
#include <iomanip>
using namespace std;
const int steps = 8;
const array<int,steps> horizontal = { 1, 2, 2, 1, -1, -2, -2, -1};
const array<int,steps> vertical = { 2, 1, -1, -2, -2, -1, 1, 2 };

void printVectorOfVectors(const vector<vector<int>> &arr) {
    for (const vector<int> &vec : arr) {
        for (int val: vec)
            cout << setw(2) << val << " ";
        cout << endl;
    }
    cout << endl;
}

bool solve_knight_step(vector<vector<int>> &chessBoard, int fieldsToOccupy, int currentX, int currentY) {
    chessBoard[currentX][currentY] = --fieldsToOccupy;
    if (fieldsToOccupy == 0)
        return true;
    for (int i = 0; i < steps; ++i) {
        int x = currentX + vertical[i];
        int y = currentY + horizontal[i];
        if (chessBoard[x][y] == 0)
            if (solve_knight_step(chessBoard, fieldsToOccupy, x, y))
                return true;
    }
    chessBoard[currentX][currentY] = 0;
    return false;
}

tuple<bool, vector<vector<int>>> solve_knight(int chessboardSize, int startingX, int startingY) {
    // returns true if solution was found
    // each cell in chessBoard contains kolejnosc ruchu
    if (startingX < 0 || startingY < 0)
        return make_tuple(false, vector<vector<int>>());
    if (startingX > chessboardSize || startingY > chessboardSize)
        return make_tuple(false, vector<vector<int>>());
    // TODO: additional requirements
    startingX += 2;
    startingY += 2;
    auto chessboard = vector<vector<int>>(chessboardSize + 4, vector<int>(chessboardSize + 4, -1));
    for (int i = 2; i < chessboardSize + 2; ++i) {
        for (int j = 2; j < chessboardSize + 2; ++j) {
            chessboard[i][j] = 0;
        }
    }
    int fieldsToOccupy = chessboardSize * chessboardSize;
    chessboard[startingX][startingY] = fieldsToOccupy;
    // printVectorOfVectors(chessboard);
    for (int stepIdx = 0; stepIdx < steps; ++stepIdx) {
        auto x = startingX + vertical[stepIdx];
        auto y = startingY + horizontal[stepIdx];
        if (chessboard[x][y] == 0) {
            if (solve_knight_step(chessboard, fieldsToOccupy, x, y))
                return make_tuple(true, chessboard);
        }

    }
    return make_tuple(false, chessboard);
}

int main(int argc, char **argv) {
    auto result = solve_knight(6, 5, 5);
    if (get<0>(result))
        cout << "Found solution" << endl;
    else
        cout << "Not found solution" << endl;
    printVectorOfVectors(get<1>(result));
    return 0;
}