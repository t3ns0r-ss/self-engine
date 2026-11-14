#include <bits/stdc++.h>
using namespace std;

vector<long long> sums(const vector<long long>& a, int from, int to) {
    vector<long long> s = {0};
    for (int i = from; i < to; i++) { int sz = s.size(); for (int j = 0; j < sz; j++) s.push_back(s[j] + a[i]); }
    return s;
}
long long bestAtMost(const vector<long long>& a, long long T) {
    int n = a.size();
    auto L = sums(a, 0, n / 2), R = sums(a, n / 2, n);
    sort(R.begin(), R.end());
    long long best = 0;
    for (long long x : L) if (x <= T) best = max(best, x + *prev(upper_bound(R.begin(), R.end(), T - x)));
    return best;
}
long long bruteAtMost(const vector<long long>& a, long long T) {
    long long best = 0;
    for (int mask = 0; mask < (1 << a.size()); mask++) {
        long long s = 0;
        for (size_t i = 0; i < a.size(); i++) if (mask >> i & 1) s += a[i];
        if (s <= T) best = max(best, s);
    }
    return best;
}
// quadruples (i, j, k, l) with A[i] + B[j] + C[k] + D[l] = 0: sort the n^2 sums of A and B, look up minus each sum of C and D
long long fourSum(const vector<long long>& A, const vector<long long>& B, const vector<long long>& C, const vector<long long>& D) {
    vector<long long> ab;
    for (long long x : A) for (long long y : B) ab.push_back(x + y);
    sort(ab.begin(), ab.end());
    long long count = 0;
    for (long long x : C) for (long long y : D) count += upper_bound(ab.begin(), ab.end(), -(x + y)) - lower_bound(ab.begin(), ab.end(), -(x + y));
    return count;
}
long long bruteFour(const vector<long long>& A, const vector<long long>& B, const vector<long long>& C, const vector<long long>& D) {
    long long count = 0;
    for (long long a : A) for (long long b : B) for (long long c : C) for (long long d : D) count += a + b + c + d == 0;
    return count;
}
// counting the subsets with sum at most T, but with lower_bound: it stops before the sums equal to T - x
long long countAtMostLower(const vector<long long>& a, long long T) {
    int n = a.size();
    auto L = sums(a, 0, n / 2), R = sums(a, n / 2, n);
    sort(R.begin(), R.end());
    long long count = 0;
    for (long long x : L) if (x <= T) count += lower_bound(R.begin(), R.end(), T - x) - R.begin();
    return count;
}
long long bruteCountAtMost(const vector<long long>& a, long long T) {
    long long count = 0;
    for (int mask = 0; mask < (1 << a.size()); mask++) {
        long long s = 0;
        for (size_t i = 0; i < a.size(); i++) if (mask >> i & 1) s += a[i];
        count += s <= T;
    }
    return count;
}
// the subset sum closest to T, looking only at the largest right sum that does not pass T - x: a sum above T is never tried
long long closestBelowOnly(const vector<long long>& a, long long T) {
    int n = a.size();
    auto L = sums(a, 0, n / 2), R = sums(a, n / 2, n);
    sort(R.begin(), R.end());
    long long best = LLONG_MAX;
    for (long long x : L) {
        auto it = upper_bound(R.begin(), R.end(), T - x);
        if (it != R.begin()) best = min(best, llabs(x + *prev(it) - T));
    }
    return best;
}
long long bruteClosest(const vector<long long>& a, long long T) {
    long long best = LLONG_MAX;
    for (int mask = 0; mask < (1 << a.size()); mask++) {
        long long s = 0;
        for (size_t i = 0; i < a.size(); i++) if (mask >> i & 1) s += a[i];
        best = min(best, llabs(s - T));
    }
    return best;
}
int main() {
    // P1: the largest subset sum at most 15 of 9 4 6 3 8. Brute: every bitmask. Method: two halves, a sorted list, upper_bound.
    vector<long long> a = {9, 4, 6, 3, 8};
    cout << "P1 brute=" << bruteAtMost(a, 15) << " method=" << bestAtMost(a, 15) << '\n';
    // P2: the quadruples with sum 0 from four lists of three numbers. Brute: all 81 quadruples. Method: sorted pair sums.
    vector<long long> A = {1, -1, 2}, B = {-2, 1, 0}, C = {0, -1, 2}, D = {1, -1, -2};
    cout << "P2 brute=" << bruteFour(A, B, C, D) << " method=" << fourSum(A, B, C, D) << '\n';
    // N1: the subsets of the single number 4 with sum at most 0 (the empty subset): lower_bound misses the sum exactly T.
    vector<long long> one = {4};
    cout << "N1 brute=" << bruteCountAtMost(one, 0) << " method=" << countAtMostLower(one, 0) << '\n';
    // N2: how far the closest subset sum of {7} is from 6 (sums 0 and 7): only sums not above T are tried, so 7 is missed.
    vector<long long> seven = {7};
    cout << "N2 brute=" << bruteClosest(seven, 6) << " method=" << closestBelowOnly(seven, 6) << '\n';
}
