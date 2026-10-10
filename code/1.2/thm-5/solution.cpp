#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.2.5. The largest subarray sum (P_j minus the smallest earlier prefix sum), and the largest a_j - a_i with i < j
// (a_j minus the smallest earlier element).
long long bestSubarray(const vector<long long>& a) {
    long long P = 0, minP = 0, best = LLONG_MIN;  // minP starts as P_0 = 0
    for (long long x : a) {
        P += x;
        best = max(best, P - minP);
        minP = min(minP, P);
    }
    return best;
}

long long bestGap(const vector<long long>& a) {
    long long minSoFar = a[0], best = LLONG_MIN;
    for (int j = 1; j < (int)a.size(); j++) {
        best = max(best, a[j] - minSoFar);
        minSoFar = min(minSoFar, a[j]);
    }
    return best;
}
// snippet:end

int main() {
    cout << "3 -5 4 -1 2: largest subarray sum " << bestSubarray({3, -5, 4, -1, 2}) << '\n';
    cout << "7 1 5 3 6 4: largest a_j - a_i with i < j: " << bestGap({7, 1, 5, 3, 6, 4}) << '\n';
    mt19937 rng(5);
    for (int round = 0; round < 400; round++) {
        int n = rng() % 7 + 2;
        vector<long long> b(n);
        for (auto& x : b) x = (long long)(rng() % 15) - 7;
        long long bs = LLONG_MIN, bg = LLONG_MIN;
        for (int l = 0; l < n; l++) for (int r = l; r < n; r++) {
            long long s = 0;
            for (int i = l; i <= r; i++) s += b[i];
            bs = max(bs, s);
        }
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) bg = max(bg, b[j] - b[i]);
        if (bs != bestSubarray(b) || bg != bestGap(b)) return 1;
    }
}
