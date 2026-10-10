/*
Problem: an R x C grid of integers and q queries "x1 y1 x2 y2" (1-based rows x1..x2, columns y1..y2);
print the sum of each rectangle.
Input: R C q (R*C <= 10^6, q <= 2*10^5), the grid (|value| <= 10^9), then the queries.
Output: one sum per line.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.2.4, parts 1 and 2. S[x][y] = sum of rows 1..x and columns 1..y (row 0 and column 0 stay 0).
vector<vector<long long>> prefix2D(const vector<vector<long long>>& a) {
    int R = a.size(), C = a[0].size();
    vector<vector<long long>> S(R + 1, vector<long long>(C + 1, 0));
    for (int x = 1; x <= R; x++)
        for (int y = 1; y <= C; y++) S[x][y] = S[x - 1][y] + S[x][y - 1] - S[x - 1][y - 1] + a[x - 1][y - 1];
    return S;
}
// The sum of rows x1..x2 and columns y1..y2 (1-based).
long long rectSum(const vector<vector<long long>>& S, int x1, int y1, int x2, int y2) {
    return S[x2][y2] - S[x1 - 1][y2] - S[x2][y1 - 1] + S[x1 - 1][y1 - 1];
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, C, q;
    cin >> R >> C >> q;
    vector<vector<long long>> a(R, vector<long long>(C));
    for (auto& row : a)
        for (auto& x : row) cin >> x;
    vector<vector<long long>> S = prefix2D(a);
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << rectSum(S, x1, y1, x2, y2) << "\n";
    }
}
