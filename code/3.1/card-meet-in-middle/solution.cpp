#include <bits/stdc++.h>
using namespace std;

long long mitmCount(const vector<long long>& a, long long T) {
    int n = a.size();
    auto sums = [&](int from, int to) {
        vector<long long> s = {0};
        for (int i = from; i < to; i++) { int sz = s.size(); for (int j = 0; j < sz; j++) s.push_back(s[j] + a[i]); }
        return s;
    };
    auto L = sums(0, n / 2), R = sums(n / 2, n);
    sort(R.begin(), R.end());
    long long c = 0;
    for (long long x : L) c += upper_bound(R.begin(), R.end(), T - x) - lower_bound(R.begin(), R.end(), T - x);
    return c;
}
// the same split, but only the sums of each half are combined: the pairs of adjacent chosen items across the middle are missed
long long mitmNoAdjacent(const vector<long long>& a, long long T) {
    int n = a.size(), h = n / 2;
    auto halfSums = [&](int from, int to) {
        vector<long long> s;
        for (int mask = 0; mask < (1 << (to - from)); mask++) {
            bool ok = true;
            long long sum = 0;
            for (int i = 0; i < to - from; i++) if (mask >> i & 1) { sum += a[from + i]; if (i + 1 < to - from && (mask >> (i + 1) & 1)) ok = false; }
            if (ok) s.push_back(sum);
        }
        return s;
    };
    auto L = halfSums(0, h), R = halfSums(h, n);
    long long c = 0;
    for (long long x : L) for (long long y : R) c += x + y == T;
    return c;
}
int main() {
    // P1: the subsets of 3 5 2 6 with sum 8. Brute: every bitmask. Method: two halves and a sorted list.
    vector<long long> a = {3, 5, 2, 6};
    int brute = 0;
    for (int mask = 0; mask < 16; mask++) {
        long long s = 0;
        for (int i = 0; i < 4; i++) if (mask >> i & 1) s += a[i];
        brute += s == 8;
    }
    cout << "P1 brute=" << brute << " method=" << mitmCount(a, 8) << '\n';
    // N1: the subsets of 4 3 4 3 with sum 7 and no two neighbours chosen. The halves ignore the neighbours across the middle.
    vector<long long> b = {4, 3, 4, 3};
    int bruteAdj = 0;
    for (int mask = 0; mask < 16; mask++) {
        long long s = 0;
        bool ok = true;
        for (int i = 0; i < 4; i++) if (mask >> i & 1) { s += b[i]; if (i + 1 < 4 && (mask >> (i + 1) & 1)) ok = false; }
        bruteAdj += ok && s == 7;
    }
    cout << "N1 brute=" << bruteAdj << " method=" << mitmNoAdjacent(b, 7) << '\n';
}
