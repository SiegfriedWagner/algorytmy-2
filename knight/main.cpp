#include <array>
#include <vector>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
const int steps = 8;
const array<int, steps> horizontal = {1, 2, 2, 1, -1, -2, -2, -1};
const array<int, steps> vertical = {2, 1, -1, -2, -2, -1, 1, 2};

void printVectorOfVectors(const vector<vector<int>> &arr) {
    for (const vector<int> &vec: arr) {
        for (int val: vec)
            cout << setw(2) << val << " ";
        cout << endl;
    }
    cout << endl;
}

bool solve_knight_step(vector<vector<int>> &chessBoard, int fieldsToOccupy, int currentX, int currentY, bool all) {
    chessBoard[currentX][currentY] = fieldsToOccupy--;
    if (fieldsToOccupy == 0) {
        printVectorOfVectors(chessBoard);
        if (!all)
            return true;
    }
    for (int i = 0; i < steps; ++i) {
        int x = currentX + vertical[i];
        int y = currentY + horizontal[i];
        if (chessBoard[x][y] == 0)
            if (solve_knight_step(chessBoard, fieldsToOccupy, x, y, all)) {
                return true;
            }
    }
    chessBoard[currentX][currentY] = 0;
    return false;
}

tuple<bool, vector<vector<int>>> solve_knight(int chessboardSize, int startingX, int startingY, bool all) {
    // returns true if solution was found
    // all - if true then generate all chessboards variants
    // each cell in chessBoard contains kolejnosc ruchu
    if (startingX < 0 || startingY < 0)
        return make_tuple(false, vector<vector<int>>());
    if (startingX > chessboardSize || startingY > chessboardSize)
        return make_tuple(false, vector<vector<int>>());
    startingX += 2;
    startingY += 2;
    auto chessboard = vector<vector<int>>(chessboardSize + 4, vector<int>(chessboardSize + 4, -1));
    for (int i = 2; i < chessboardSize + 2; ++i) {
        for (int j = 2; j < chessboardSize + 2; ++j) {
            chessboard[i][j] = 0;
        }
    }
    tuple<bool, vector<vector<int>>> result(false, {});
    int fieldsToOccupy = chessboardSize * chessboardSize;
    chessboard[startingX][startingY] = fieldsToOccupy--;
    // printVectorOfVectors(chessboard);
    for (int stepIdx = 0; stepIdx < steps; ++stepIdx) {
        auto x = startingX + vertical[stepIdx];
        auto y = startingY + horizontal[stepIdx];
        if (chessboard[x][y] == 0) {
            if (solve_knight_step(chessboard, fieldsToOccupy, x, y, all)) {
                result = make_tuple(true, chessboard);
                if (!all)
                    break;
            }
        }

    }
    return result;
}

int main(int argc, char **argv) {
    if (argc < 5) {
        cout << "Missig arguments {chessboardSize:int} {startingX:int} {startingY:int} {findAll: bool[true,false]}"
             << endl;
        return 1;
    }
    int chessBoardSize = stoi(string(argv[1]));
    int startingX = stoi(string(argv[2]));
    int startingY = stoi(string(argv[3]));
    auto last = string(argv[4]);
    bool all;
    if (last == "true") {
        all = true;
    } else if (last == "false") {
        all = false;
    } else {
        cout << "Ambiguous string" << endl;
        return 2;
    }
    auto result = solve_knight(chessBoardSize, startingX, startingY, all);
    // printVectorOfVectors(get<1>(result));
    return 0;
}