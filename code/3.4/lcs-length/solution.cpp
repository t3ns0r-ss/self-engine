/*
Problem: the length of the longest common subsequence of two strings.
Input: two lines, strings a and b of lowercase letters (1 <= |a|, |b| <= 5000).
Output: the length.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    // two rows of the table C[i][j] over prefix pairs (Theorem 3.4.4)
    vector<int> prev(m + 1, 0), cur(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) cur[j] = prev[j - 1] + 1;  // match the two last characters
            else cur[j] = max(prev[j], cur[j - 1]);           // skip a_i or skip b_j
        }
        swap(prev, cur);  // the row just filled becomes the previous row
    }
    cout << prev[m] << "\n";
}
