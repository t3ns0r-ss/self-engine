#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 7.6.4. The same power trick works over the semiring (min, +): "sum" is min, "product" is +, the identity has 0 on the diagonal
// and INF elsewhere. Then entry (i, j) of weights^L is the least total weight of a walk with exactly L edges from i to j (INF if none).
using Matrix = vector<vector<long long>>;
const long long INF = (long long)2e18;
Matrix minPlusMultiply(const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix c(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                if (a[i][k] < INF && b[k][j] < INF) c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
    return c;
}
Matrix minPlusPower(Matrix base, long long e) {
    int n = base.size();
    Matrix result(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) result[i][i] = 0;
    for (; e > 0; e >>= 1, base = minPlusMultiply(base, base))
        if (e & 1) result = minPlusMultiply(result, base);
    return result;
}
// snippet:end

Matrix bruteLayers(const Matrix& w, int length) {  // the best walk with exactly `length` edges, one layer at a time
    int n = w.size();
    Matrix best(n, vector<long long>(n, INF));
    for (int s = 0; s < n; s++) {
        vector<long long> cur(n, INF);
        cur[s] = 0;
        for (int step = 0; step < length; step++) {
            vector<long long> next(n, INF);
            for (int u = 0; u < n; u++)
                for (int v = 0; v < n; v++)
                    if (cur[u] < INF && w[u][v] < INF) next[v] = min(next[v], cur[u] + w[u][v]);
            cur = next;
        }
        best[s] = cur;
    }
    return best;
}

int main() {
    Matrix w(4, vector<long long>(4, INF));
    w[0][1] = 4, w[0][2] = 1, w[2][1] = 1, w[1][3] = 2, w[2][3] = 6;
    for (int len : {2, 3, 1}) {
        long long d = minPlusPower(w, len)[0][3];
        cout << "least weight of a walk of length " << len << " from 0 to 3: ";
        if (d < INF) cout << d << "\n";
        else cout << "none\n";
    }
    // Check (not printed): 500 random graphs of 5 vertices (weights 1 to 9 or no edge), lengths 0 to 7, all pairs.
    mt19937 rng(11);
    for (int round = 0; round < 500; round++) {
        Matrix a(5, vector<long long>(5, INF));
        for (auto& row : a)
            for (auto& x : row)
                if (rng() % 3) x = 1 + rng() % 9;
        for (int len = 0; len <= 7; len++)
            if (minPlusPower(a, len) != bruteLayers(a, len)) return 1;
    }
}
