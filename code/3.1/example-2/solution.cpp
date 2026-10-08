/*
Problem: AtCoder ABC 184 F, Programming Contest. Choose some of N problems with times A_i so that the total
time is at most T, and print the largest such total.
Input: N T (N <= 40, T <= 10^9), then A_1 .. A_N (each <= 10^9).
Output: the largest subset sum that is at most T.
*/
#include <bits/stdc++.h>
using namespace std;

// all subset sums of v[from..to-1] (up to 2 * 10^10: long long)
vector<long long> subsetSums(const vector<long long>& v, int from, int to) {
    vector<long long> sums = {0};
    for (int i = from; i < to; i++) {
        int size = sums.size();
        for (int j = 0; j < size; j++) sums.push_back(sums[j] + v[i]);
    }
    return sums;
}

int main() {
    int n;
    long long T;
    cin >> n >> T;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<long long> left = subsetSums(a, 0, n / 2);
    vector<long long> right = subsetSums(a, n / 2, n);
    sort(right.begin(), right.end());
    long long best = 0;  // the empty choice
    for (long long x : left) {
        if (x > T) continue;
        // the largest right sum y <= T - x is just before the first one that is larger (Theorem 3.1.4)
        auto it = upper_bound(right.begin(), right.end(), T - x);
        best = max(best, x + *prev(it));  // right contains 0 <= T - x, so it != right.begin()
    }
    cout << best << "\n";
}
