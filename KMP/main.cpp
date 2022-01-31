//
// Created by mateu on 24.01.2022.
//
#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> buildPartialMatchTable(const string &pattern) {
    vector<int> result(pattern.size(), 0);
    int j = 0;
    int i = 1;
    while(i < pattern.size()) {
        if (pattern[i] == pattern[j]) {
            j++;
            result[i] = j;
            i++;
        }
        else {
            if (j != 0) {
                j = result[j - 1];
            } else {
                result[j] = 0;
                i++;
            }
        }
    }
    return result;
}
// searches for pattern in text and returns list of indexes where pattern starts in text
vector<int> KMPSearch(const string &pattern, const string &text) {
    vector<int> result;
    auto partial_match_table = buildPartialMatchTable(pattern);
    int pattern_index = 0;
    for(int index = 0; index < text.size(); index++) {
        if (pattern[pattern_index] == text[index]) {
            pattern_index++;
            if (pattern_index == pattern.size()) {
                result.push_back(index - pattern_index + 1);
                pattern_index = partial_match_table[pattern_index - 1];
            }
        }
        else while(pattern[pattern_index] != text[index] && pattern_index != 0) {
            pattern_index = partial_match_table[pattern_index - 1];
        }
    }
    return result;
}


int main(int argc, char **argv) {
    string text("ABABDABACDABABCABAB");
    //string text("ABABABCABABAB");
    string pattern("ABA");
    // string pattern("ABABCABAB");
    auto match_indexes = KMPSearch(pattern, text);
    if (!match_indexes.empty()) {
        cout << "Found patterns at: ";
        for (auto start_index: match_indexes)
            cout << start_index << " ";
    }
    else
        cout << "No patterns found";
    cout << endl;
    return 0;
}