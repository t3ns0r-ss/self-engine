#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.2.4. S[x][y] = sum of rows 1..x and columns 1..y; a rectangle (0-based corners) from four S values.
vector<vector<long long>> prefix2D(const vector<vector<long long>>& a) {
    int R = a.size(), C = a[0].size();
    vector<vector<long long>> S(R + 1, vector<long long>(C + 1, 0));
    for (int x = 1; x <= R; x++)
        for (int y = 1; y <= C; y++) S[x][y] = S[x - 1][y] + S[x][y - 1] - S[x - 1][y - 1] + a[x - 1][y - 1];
    return S;
}
long long rectSum(const vector<vector<long long>>& S, int x1, int y1, int x2, int y2) {
    return S[x2 + 1][y2 + 1] - S[x1][y2 + 1] - S[x2 + 1][y1] + S[x1][y1];
}
// snippet:end

int main() {
    vector<vector<long long>> a = {{1, 2, 3}, {4, 5, 6}}, S = prefix2D(a);
    for (int x = 1; x <= 2; x++) {
        cout << "S row " << x << ":";
        for (long long v : S[x]) cout << ' ' << v;
        cout << '\n';
    }
    cout << "rectangle rows 0..1, columns 1..2: " << rectSum(S, 0, 1, 1, 2) << '\n';
    cout << "rectangle rows 1..1, columns 1..1: " << rectSum(S, 1, 1, 1, 1) << '\n';
    mt19937 rng(4);
    for (int round = 0; round < 200; round++) {
        int R = rng() % 4 + 1, C = rng() % 4 + 1;
        vector<vector<long long>> g(R, vector<long long>(C));
        for (auto& row : g) for (auto& v : row) v = (long long)(rng() % 9) - 4;
        auto T2 = prefix2D(g);
        for (int x1 = 0; x1 < R; x1++) for (int x2 = x1; x2 < R; x2++) for (int y1 = 0; y1 < C; y1++) for (int y2 = y1; y2 < C; y2++) {
            long long s = 0;
            for (int x = x1; x <= x2; x++) for (int y = y1; y <= y2; y++) s += g[x][y];
            if (s != rectSum(T2, x1, y1, x2, y2)) return 1;
        }
    }
}
