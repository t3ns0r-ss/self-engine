#include <bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<long long>>;
const long long INF = (long long)2e18;
const long long NEG = (long long)-2e18;
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
long long layers(const Matrix& w, int from, int to, int len) {  // brute: one layer at a time
    int n = w.size();
    vector<long long> cur(n, INF);
    cur[from] = 0;
    for (int s = 0; s < len; s++) {
        vector<long long> next(n, INF);
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (cur[u] < INF && w[u][v] < INF) next[v] = min(next[v], cur[u] + w[u][v]);
        cur = next;
    }
    return cur[to];
}
// longest non-decreasing subsequence of [3, 1, 2] written 3 times, by the quadratic loop, and by the (max, +) power of the matrix with the state = the last value
int main() {
    Matrix w(4, vector<long long>(4, INF));
    w[0][1] = 4, w[0][2] = 1, w[2][1] = 1, w[1][3] = 2, w[2][3] = 6;
    // P1: the cheapest walk with exactly 3 edges from 0 to 3
    cout << "P1 brute=" << layers(w, 0, 3, 3) << " method=" << minPlusPower(w, 3)[0][3] << "\n";
    // P2: [3, 1, 2] three times
    vector<int> all;
    for (int t = 0; t < 3; t++) all.insert(all.end(), {3, 1, 2});
    vector<int> best(all.size(), 1);
    int answer = 0;
    for (size_t i = 0; i < all.size(); i++) {
        for (size_t j = 0; j < i; j++)
            if (all[j] <= all[i]) best[i] = max(best[i], best[j] + 1);
        answer = max(answer, best[i]);
    }
    // one pass over [3, 1, 2], states = the values 1, 2, 3 (index 0, 1, 2): one[u][v] = the most elements added, last value u -> v
    Matrix one(3, vector<long long>(3, NEG));
    vector<int> a = {3, 1, 2};
    for (int u = 0; u < 3; u++) {
        vector<long long> bestEnd(3, NEG);
        bestEnd[u] = 0;
        for (int x : a) {
            int v = x - 1;
            if (v < u) continue;
            long long before = NEG;
            for (int q = u; q <= v; q++) before = max(before, bestEnd[q]);
            if (before > NEG) bestEnd[v] = max(bestEnd[v], before + 1);
        }
        one[u] = bestEnd;
    }
    Matrix p(3, vector<long long>(3, NEG));
    for (int i = 0; i < 3; i++) p[i][i] = 0;
    for (int rep = 0; rep < 3; rep++) {
        Matrix c(3, vector<long long>(3, NEG));
        for (int i = 0; i < 3; i++)
            for (int k = 0; k < 3; k++)
                for (int j = 0; j < 3; j++)
                    if (p[i][k] > NEG && one[k][j] > NEG) c[i][j] = max(c[i][j], p[i][k] + one[k][j]);
        p = c;
    }
    cout << "P2 brute=" << answer << " method=" << *max_element(p[0].begin(), p[0].end()) << "\n";
    // N1: the cheapest walk from 0 to 3 with any number of edges (at most 3 here), against the walk with exactly 2 edges
    long long shortest = INF;
    for (int len = 0; len <= 3; len++) shortest = min(shortest, layers(w, 0, 3, len));
    cout << "N1 brute=" << shortest << " method=" << minPlusPower(w, 2)[0][3] << "\n";
}
