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

void permute(int wordLenght, vector<int> &dictionary, vector<int> &symbols) {

    _permute(size, array);
}

int main() {
    // permutacje - n = dictionarySum, dictionarySum[k] = 1 : k = 0, 1, ... m
    // wariacje bez powrotrzen  n < dictionarySum, dictionarySym[k] = 1 : k = 0, 1, ...
    // wariacje z powtorzeniami n < dictionarySum, dictionarySum[k] > 0 : k = 0, 1, ...
    vector<int> dictionary = { 1, 1, 1, 1, 1 }; // liczba dostepnych symboli
    vector<int> symbols = { 1, 2, 3, 4, 5 }; // zbior symboli
    int n = 5; // dlugosc szykanych kombinacji
    int dictionarySum = 0;
    for(int i : dictionary)
        dictionarySum += i;
    if (n > dictionarySum) {
        cout << "Za dlugie wyrazy" << endl;
        return 1;
    }
    permute(n, dictionary, symbols);
    return 0;
}