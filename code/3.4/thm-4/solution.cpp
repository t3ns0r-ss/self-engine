#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.4.4. C[i][j] = the LCS length of the prefixes of lengths i and j: a match extends the diagonal, otherwise skip a
// character on one side. Returns the whole table.
vector<vector<int>> lcsTable(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> C(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            C[i][j] = a[i - 1] == b[j - 1] ? C[i - 1][j - 1] + 1 : max(C[i - 1][j], C[i][j - 1]);
    return C;
}
// snippet:end

int main() {
    string a = "ACB", b = "ABC";
    auto C = lcsTable(a, b);
    cout << "rows A C B, columns A B C:\n";
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) cout << C[i][j] << (j < 3 ? ' ' : '\n');
    }
    cout << "LCS length " << C[3][3] << '\n';
    mt19937 rng(34);
    for (int round = 0; round < 300; round++) {
        string x, y;
        for (int i = rng() % 8; i > 0; i--) x += 'a' + rng() % 3;
        for (int i = rng() % 8; i > 0; i--) y += 'a' + rng() % 3;
        int best = 0;
        for (int mask = 0; mask < (1 << x.size()); mask++) {
            string s;
            for (size_t i = 0; i < x.size(); i++) if (mask >> i & 1) s += x[i];
            size_t p = 0;
            for (char ch : y) if (p < s.size() && s[p] == ch) p++;
            if (p == s.size()) best = max(best, (int)s.size());
        }
        if (best != lcsTable(x, y)[x.size()][y.size()]) return 1;
    }
}
