#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.4.6. The k-th smallest entry of the n x n multiplication table: the smallest x with count(x) >= k,
// where count(x) = sum over rows i of min(n, x / i) entries at most x.
long long kthInTable(long long n, long long k) {
    auto count = [&](long long x) {
        long long c = 0;
        for (long long i = 1; i <= n; i++) c += min(n, x / i);
        return c;
    };
    long long lo = 0, hi = n * n;  // count(0) = 0 < k, count(n * n) = n * n >= k
    while (hi - lo > 1) {
        long long mid = lo + (hi - lo) / 2;
        if (count(mid) >= k) hi = mid;
        else lo = mid;
    }
    return hi;
}
// snippet:end

int main() {
    cout << "3 x 3 table, 5th smallest: " << kthInTable(3, 5) << '\n';
    cout << "3 x 3 table, 9th smallest: " << kthInTable(3, 9) << '\n';
    cout << "3 x 3 table, 1st smallest: " << kthInTable(3, 1) << '\n';
    for (int n = 1; n <= 8; n++) {
        vector<int> all;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) all.push_back(i * j);
        sort(all.begin(), all.end());
        for (int k = 1; k <= n * n; k++) if (kthInTable(n, k) != all[k - 1]) return 1;
    }
}
