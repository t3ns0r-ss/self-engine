#include <bits/stdc++.h>
using namespace std;

/*
Problem: an array of n <= 100 numbers (each up to 300) is written T times one after another (T up to 10^7). Print the length of the longest
non-decreasing subsequence of the long array.
Input: n and T, then the n numbers.
Output: the length.
*/

using Mat = vector<vector<long long>>;
const long long NEG = (long long)-2e18;
Mat maxPlusMultiply(const Mat& a, const Mat& b) {
    int n = a.size();
    Mat c(n, vector<long long>(n, NEG));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                if (a[i][k] > NEG && b[k][j] > NEG) c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
    return c;
}
Mat maxPlusPower(Mat base, long long e) {
    int n = base.size();
    Mat result(n, vector<long long>(n, NEG));
    for (int i = 0; i < n; i++) result[i][i] = 0;
    for (; e > 0; e >>= 1, base = maxPlusMultiply(base, base))
        if (e & 1) result = maxPlusMultiply(result, base);
    return result;
}

// snippet:begin
// Theorem 7.6.4 over the semiring (max, +). The state is the last chosen value (compressed to 0 ... V-1). one[u][v] = the most elements that
// one copy of the array can add to a non-decreasing subsequence whose last value is u, ending with the value v >= u. T copies = one^T.
long long longestRepeated(const vector<int>& a, long long T) {
    vector<int> values = a;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    int V = values.size();
    Mat one(V, vector<long long>(V, NEG));
    for (int u = 0; u < V; u++) {
        vector<long long> best(V, NEG);
        best[u] = 0;
        for (int x : a) {
            int v = lower_bound(values.begin(), values.end(), x) - values.begin();
            if (v < u) continue;
            long long before = *max_element(best.begin() + u, best.begin() + v + 1);
            if (before > NEG) best[v] = max(best[v], before + 1);
        }
        one[u] = best;
    }
    Mat p = maxPlusPower(one, T);
    return *max_element(p[0].begin(), p[0].end());  // the smallest value is the start state
}
// snippet:end

int main() {
    int n;
    long long T;
    cin >> n >> T;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << longestRepeated(a, T) << "\n";
}
