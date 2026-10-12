#include <bits/stdc++.h>
using namespace std;

/*
Problem: a string s of n letters 'I' and 'D' (n up to 8). Print the lexicographically smallest permutation of 1 ... n + 1 in which the i-th
neighbours go up when s_i = 'I' and down when s_i = 'D'.
Input: the string s.
Output: the permutation, numbers separated by spaces.
*/

// snippet:begin
// Start from 1, 2, ..., n + 1 and reverse every maximal block of 'D': a run of d letters 'D' covers d + 1 positions, which become decreasing.
vector<int> smallestMatching(const string& s) {
    int n = s.size();
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 1);
    for (int i = 0; i < n;) {
        if (s[i] != 'D') {
            i++;
            continue;
        }
        int j = i;
        while (j < n && s[j] == 'D') j++;
        reverse(p.begin() + i, p.begin() + j + 1);
        i = j;
    }
    return p;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    auto p = smallestMatching(s);
    for (size_t i = 0; i < p.size(); i++) cout << p[i] << (i + 1 < p.size() ? " " : "\n");
}
