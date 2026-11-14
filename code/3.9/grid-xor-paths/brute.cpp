// Brute force: follow every path (Theorem 0.5.4) and compare its xor with k.
#include <bits/stdc++.h>
using namespace std;

int n, m;
long long k, answer = 0;
vector<vector<long long>> a;

void walk(int i, int j, long long x) {
    x ^= a[i][j];
    if (i == n - 1 && j == m - 1) { answer += x == k; return; }
    if (i + 1 < n) walk(i + 1, j, x);
    if (j + 1 < m) walk(i, j + 1, x);
}

int main() {
    cin >> n >> m >> k;
    a.assign(n, vector<long long>(m));
    for (auto& row : a) for (auto& x : row) cin >> x;
    walk(0, 0, 0);
    cout << answer << "\n";
}
