#include <iostream>
#include <vector>

using namespace std;
void printArray(const vector<int> &array) {
    for (int i : array)
        cout << i << " ";
    cout << endl;
}

void _permute(int wordLength, vector<int> &dictionary, vector<int> &symbols, vector<int> &word) {
    if (wordLength == word.size())
        printArray(word);
    else
        for (int i = 0; i < dictionary.size(); i++) {
            if (dictionary[i] > 0)
            {
                dictionary[i]--;
                word[wordLength] = symbols[i];
                _permute(wordLength + 1, dictionary, symbols, word);
                dictionary[i]++;
                word[wordLength] = 0;
            }
    }
}

void permute(vector<int> &dictionary, vector<int> &symbols, vector<int> &word) {
    _permute(0, dictionary, symbols, word);
}

int main() {
    // permutacje - n = dictionarySum, dictionarySum[k] = 1 : k = 0, 1, ... m
    // wariacje bez powrotrzen  n < dictionarySum, dictionarySym[k] = 1 : k = 0, 1, ...
    // wariacje z powtorzeniami n < dictionarySum, dictionarySum[k] > 0 : k = 0, 1, ...
    int n = 5; // dlugosc szukanych kombinacji
    vector<int> dictionary = { 2, 2, 1  }; // liczba dostepnych symboli
    vector<int> symbols = { 1, 2, 3}; // zbior symboli
    vector<int> word(n, 0);
    int dictionarySum = 0;
    for(int i : dictionary)
        dictionarySum += i;
    if (n > dictionarySum) {
        cout << "Za dlugie wyrazy" << endl;
        return 1;
    }
    permute(dictionary, symbols, word);
    return 0;
}