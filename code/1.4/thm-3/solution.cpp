#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.4.3. The smallest x in L..R with ok(x) (ok monotone, ok(R) true), and a use: cut an array into at most k
// consecutive parts so that the largest part sum is as small as possible.
long long smallestWorking(long long L, long long R, const function<bool(long long)>& ok) {
    long long lo = L - 1, hi = R;  // ok(lo) is false (agreed), ok(hi) is true
    while (hi - lo > 1) {
        long long mid = lo + (hi - lo) / 2;
        if (ok(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}

long long minLargestPart(const vector<long long>& a, int k) {
    auto ok = [&](long long x) {  // fill each part as much as possible; are k parts enough?
        int parts = 1;
        long long cur = 0;
        for (long long v : a) {
            if (v > x) return false;
            if (cur + v > x) parts++, cur = 0;
            cur += v;
        }
        return parts <= k;
    };
    return smallestWorking(1, accumulate(a.begin(), a.end(), 0LL), ok);
}
// snippet:end

int main() {
    cout << "smallest x in 1..100 with x * x >= 50: " << smallestWorking(1, 100, [](long long x) { return x * x >= 50; }) << '\n';
    cout << "smallest x in 1..100 with 3 * x >= 100: " << smallestWorking(1, 100, [](long long x) { return 3 * x >= 100; }) << '\n';
    cout << "2 4 7 3 5 cut into at most 3 parts, smallest largest part: " << minLargestPart({2, 4, 7, 3, 5}, 3) << '\n';
    mt19937 rng(2);
    for (int round = 0; round < 300; round++) {
        int n = rng() % 6 + 1, k = rng() % n + 1;
        vector<long long> a(n);
        for (auto& v : a) v = rng() % 9 + 1;
        long long best = LLONG_MAX;  // every way to place k - 1 cuts among the n - 1 gaps (up to k parts)
        for (int mask = 0; mask < (1 << (n - 1)); mask++) {
            if (__builtin_popcount(mask) > k - 1) continue;
            long long cur = 0, mx = 0;
            for (int i = 0; i < n; i++) {
                cur += a[i];
                if (i == n - 1 || (mask >> i & 1)) mx = max(mx, cur), cur = 0;
            }
            best = min(best, mx);
        }
        if (best != minLargestPart(a, k)) return 1;
    }
}
