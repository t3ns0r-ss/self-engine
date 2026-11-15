#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.6. Per-bit sums over all subarrays of one array and over all pairs taken from two arrays.
long long subarrayXorSum(const vector<int>& a) {
    int n = a.size();
    vector<int> p(n + 1, 0);  // p[k] = a[0] ^ ... ^ a[k-1]; a subarray's XOR is p[l] ^ p[r + 1]
    for (int k = 0; k < n; k++) p[k + 1] = p[k] ^ a[k];
    long long total = 0;
    for (int b = 0; b < 30; b++) {
        long long ones = 0;  // how many of the n + 1 prefix values have bit b
        for (int v : p) ones += (v >> b) & 1;
        total += (1LL << b) * ones * (n + 1 - ones);  // pairs of prefix values that differ at bit b
    }
    return total;
}
long long andSumOfTwoArrays(const vector<int>& x, const vector<int>& y) {
    long long total = 0;
    for (int b = 0; b < 30; b++) {
        long long cx = 0, cy = 0;
        for (int v : x) cx += (v >> b) & 1;
        for (int v : y) cy += (v >> b) & 1;
        total += (1LL << b) * cx * cy;  // x_i & y_j has bit b exactly when both have it
    }
    return total;
}
int xorOfAllAnds(const vector<int>& x, const vector<int>& y) {
    int fx = 0, fy = 0;
    for (int v : x) fx ^= v;
    for (int v : y) fy ^= v;
    return fx & fy;  // bit b is the parity of cx * cy, which is odd only when both counts are odd
}
// snippet:end

int main() {
    cout << "subarray XOR sum of 1 2 3: " << subarrayXorSum({1, 2, 3}) << '\n';
    cout << "subarray XOR sum of 5 5 5: " << subarrayXorSum({5, 5, 5}) << '\n';
    cout << "pairs of (3 1) and (2 3): AND sum " << andSumOfTwoArrays({3, 1}, {2, 3}) << ", XOR of all " << xorOfAllAnds({3, 1}, {2, 3}) << '\n';
    // Check the three claims against brute force on every small input.
    // All arrays of length 0..5 with values 0..7.
    for (int n = 0; n <= 5; n++) {
        int count = 1;
        for (int i = 0; i < n; i++) count *= 8;
        for (int code = 0; code < count; code++) {
            vector<int> a(n);
            int c = code;
            for (int i = 0; i < n; i++) a[i] = c % 8, c /= 8;
            long long want = 0;
            for (int l = 0; l < n; l++) {
                int x = 0;
                for (int r = l; r < n; r++) x ^= a[r], want += x;
            }
            if (want != subarrayXorSum(a)) return 1;
        }
    }
    // All pairs of arrays of length 0..3 with values 0..7.
    for (int p = 0; p <= 3; p++)
        for (int q = 0; q <= 3; q++) {
            int cp = 1, cq = 1;
            for (int i = 0; i < p; i++) cp *= 8;
            for (int i = 0; i < q; i++) cq *= 8;
            for (int u = 0; u < cp; u++)
                for (int v = 0; v < cq; v++) {
                    vector<int> x(p), y(q);
                    int cu = u, cv = v;
                    for (int i = 0; i < p; i++) x[i] = cu % 8, cu /= 8;
                    for (int i = 0; i < q; i++) y[i] = cv % 8, cv /= 8;
                    long long sum = 0;
                    int xr = 0;
                    for (int i : x) for (int j : y) sum += i & j, xr ^= i & j;
                    if (sum != andSumOfTwoArrays(x, y) || xr != xorOfAllAnds(x, y)) return 1;
                }
        }
}
