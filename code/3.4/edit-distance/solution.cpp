/*
Problem: the edit distance between two strings: the fewest single-character insertions, deletions and
replacements that turn a into b.
Input: two lines, strings a and b of lowercase letters (1 <= |a|, |b| <= 5000).
Output: the edit distance.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.4.5. E[i][j] over prefix pairs, stored as two rows.
int editDistance(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<int> prev(m + 1), cur(m + 1);
    for (int j = 0; j <= m; j++) prev[j] = j;  // empty prefix of a: j insertions
    for (int i = 1; i <= n; i++) {
        cur[0] = i;  // i deletions
        for (int j = 1; j <= m; j++) {
            int replace = prev[j - 1] + (a[i - 1] != b[j - 1]);  // last column (a_i, b_j)
            cur[j] = min({prev[j] + 1, cur[j - 1] + 1, replace});  // delete a_i, insert b_j, or align them
        }
        swap(prev, cur);
    }
    return prev[m];
}
// snippet:end

int main() {
    string a, b;
    cin >> a >> b;
    cout << editDistance(a, b) << "\n";
}
