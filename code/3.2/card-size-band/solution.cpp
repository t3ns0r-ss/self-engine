#include <bits/stdc++.h>
using namespace std;

vector<long long> sums(const vector<long long>& a, int from, int to) {
    vector<long long> s = {0};
    for (int i = from; i < to; i++) { int sz = s.size(); for (int j = 0; j < sz; j++) s.push_back(s[j] + a[i]); }
    return s;
}
long long mitmCount(const vector<long long>& a, long long T) {
    int n = a.size();
    auto L = sums(a, 0, n / 2), R = sums(a, n / 2, n);
    sort(R.begin(), R.end());
    long long c = 0;
    for (long long x : L) c += upper_bound(R.begin(), R.end(), T - x) - lower_bound(R.begin(), R.end(), T - x);
    return c;
}
long long mitmBest(const vector<long long>& a, long long T) {
    int n = a.size();
    auto L = sums(a, 0, n / 2), R = sums(a, n / 2, n);
    sort(R.begin(), R.end());
    long long best = 0;
    for (long long x : L) if (x <= T) best = max(best, x + *prev(upper_bound(R.begin(), R.end(), T - x)));
    return best;
}
long long bruteBest(const vector<long long>& a, long long T) {
    long long best = 0;
    for (int mask = 0; mask < (1 << a.size()); mask++) {
        long long s = 0;
        for (size_t i = 0; i < a.size(); i++) if (mask >> i & 1) s += a[i];
        if (s <= T) best = max(best, s);
    }
    return best;
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
    // P2: the largest subset sum at most 20 of 7 11 5 9 4 13.
    vector<long long> b = {7, 11, 5, 9, 4, 13};
    cout << "P2 brute=" << bruteBest(b, 20) << " method=" << mitmBest(b, 20) << '\n';
    // N1: the subsets of 4 3 4 3 with sum 7 and no two neighbours chosen. The halves ignore the neighbours across the middle.
    vector<long long> c = {4, 3, 4, 3};
    int bruteAdj = 0;
    for (int mask = 0; mask < 16; mask++) {
        long long s = 0;
        bool ok = true;
        for (int i = 0; i < 4; i++) if (mask >> i & 1) { s += c[i]; if (i + 1 < 4 && (mask >> (i + 1) & 1)) ok = false; }
        bruteAdj += ok && s == 7;
    }
    cout << "N1 brute=" << bruteAdj << " method=" << mitmNoAdjacent(c, 7) << '\n';
    // N2: 50 numbers all equal to 1, subsets with sum at most 10: a binomial sum. Two halves would list 2^25 sums each.
    long long total = 0, binom = 1;
    for (int k = 0; k <= 10; k++) { total += binom; binom = binom * (50 - k) / (k + 1); }
    int halfSize = 50 / 2;
    cout << "N2 brute=" << total << " method=" << ((1LL << halfSize) > (1LL << 22) ? "too-slow" : "ok") << '\n';
}
