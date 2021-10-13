#include <iostream>
#include <vector>
using namespace std;
void printArray(const vector<int> &array) {
    for (int i : array)
        cout << i << " ";
    cout << endl;
}

void _permute(int k, vector<int> &array) {
    if (k == 0)
        printArray(array);
    else
        for (int i = k - 1; i >= 0; i--) {
            swap(array[i], array[k - 1]);
            _permute(k - 1, array);
            swap(array[i], array[k - 1]);
    }
}

void permute(int size) {
    vector<int> array(size);
    for (int i = 0; i < array.size(); ++i)
        array[i] = i;
    _permute(size, array);
}

int main() {
    permute(5);
    return 0;
}