#include <array>
#include <vector>
#include <cassert>
#include <iostream>
#include "../vector_helpers.h"

using namespace std;
const int32_t forbiddenStep = -1;
const int32_t unset = 0;
const int8_t steps = 8;
const array<int32_t, steps> horizontal = {1, 2, 2, 1, -1, -2, -2, -1};
const array<int32_t, steps> vertical = {2, 1, -1, -2, -2, -1, 1, 2};
using neigh_t = int32_t;

bool solve_warnsdoff(vector<vector<int32_t>> &board, vector<vector<neigh_t>> &neighbours, const int32_t currentX,
                     const int32_t currentY, int32_t stepsRemaining) {
    if (stepsRemaining == 0)
        return true;
    array<neigh_t, steps> visitingOrder = {-1, -1, -1, -1, -1, -1, -1, -1};
    board[currentX][currentY] = stepsRemaining--;
    for (auto i = 0; i < steps; ++i) {
        auto x = currentX + vertical[i];
        auto y = currentY + horizontal[i];
        neighbours[x][y]--;
        assert(neighbours[x][y] >= 0);
    }
    // calculate visiting order
    {
        array<array<neigh_t, steps + 1>, steps> tempArray = {{0}}; // tempArray[n][m] - helper finite size dictionary
        for(auto i = 0; i < steps; i++) {
            auto x = currentX + vertical[i];
            auto y = currentY + horizontal[i];
            auto neigh = neighbours[x][y];
            if (board[x][y] != unset)
                continue;
            else {
                tempArray[neigh][tempArray[neigh][0]+1] = i;
                tempArray[neigh][0]++;
            }
        }
        int32_t visitingOrderFillIndex = 0;
        for (auto i = 0; i < steps; ++i) {
            for (auto j = 1; j <= tempArray[i][0]; ++j) {
                assert(visitingOrderFillIndex < steps);
                visitingOrder[visitingOrderFillIndex++] = tempArray[i][j];
            }
        }
    }
    {
        // step forward
        auto i = 0;
        while (visitingOrder[i] != -1) {
            auto newX = currentX + vertical[visitingOrder[i]];
            auto newY = currentY + horizontal[visitingOrder[i]];
            if (solve_warnsdoff(board, neighbours, newX, newY, stepsRemaining))
                return true;
            i++;
        }
    }
    board[currentX][currentY] = unset;
    for (auto i = 0; i < steps; ++i) {
        auto x = currentX + vertical[i];
        auto y = currentY + horizontal[i];
        neighbours[x][y]++;
    }
    return false;
}

int main(int32_t argc, char **argv) {
    if (argc < 3) {
        cout << "Missing argument {chessboardSize:int} {startingX:int} {startingY:int}" << endl;
        return 1;
    }
    int32_t chessBoardSize = stoi(string(argv[1]));
    int32_t startingX = stoi(string(argv[2]));
    int32_t startingY = stoi(string(argv[3]));
    if (startingX >= chessBoardSize || startingX < 0) {
        cout << "Invalid x" << endl;
        return 2;
    }
    if (startingY >= chessBoardSize || startingY < 0) {
        cout << "Invalid y" << endl;
        return 3;
    }
    vector<vector<int32_t>> board((chessBoardSize + 4), vector<int32_t>(chessBoardSize + 4, forbiddenStep));
    for (int32_t i = 2; i < chessBoardSize + 2; ++i)
        for (int32_t j = 2; j < chessBoardSize + 2; ++j)
            board[i][j] = unset;
    // printVectorOfVectors(board);
    vector<vector<neigh_t>> numberOfValidNeighbours((chessBoardSize + 4), vector<neigh_t>(chessBoardSize + 4, 10));
    for (int32_t i = 2; i < chessBoardSize + 2; ++i) {
        for (int32_t j = 2; j < chessBoardSize + 2; ++j) {
            neigh_t valid_neighbours = 0;
            for (int8_t step = 0; step < steps; step++) {
                int32_t x = i + vertical[step];
                int32_t y = j + horizontal[step];
                if (board[x][y] == 0)
                    valid_neighbours++;
            }
            numberOfValidNeighbours[i][j] = valid_neighbours;
        }
    }
    startingX += 2;
    startingY += 2;
    printVectorOfVectors(numberOfValidNeighbours);
    if (solve_warnsdoff(board, numberOfValidNeighbours, startingX, startingY, chessBoardSize * chessBoardSize - 1))
        printVectorOfVectors(board);
    else
        cout << "not found" << endl;
    return 0;
}