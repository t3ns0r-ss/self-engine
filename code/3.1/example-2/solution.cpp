/*
Problem: AtCoder ABC 184 F, Programming Contest. Choose some of N problems with times A_i so that the total
time is at most T, and print the largest such total.
Input: N T (N <= 40, T <= 10^9), then A_1 .. A_N (each <= 10^9).
Output: the largest subset sum that is at most T.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// All subset sums of v[from..to-1], built one element at a time (sums reach 4 * 10^10: long long).
vector<long long> subsetSums(const vector<long long>& v, int from, int to) {
    vector<long long> sums = {0};
    for (int i = from; i < to; i++) {
        int size = sums.size();
        for (int j = 0; j < size; j++) sums.push_back(sums[j] + v[i]);
    }
    return sums;
}
// ABC 184 F. The largest subset sum at most T: the largest right sum y <= T - x is just before the first one that is larger.
long long bestSubsetSum(const vector<long long>& a, long long T) {
    int n = a.size();
    vector<long long> left = subsetSums(a, 0, n / 2), right = subsetSums(a, n / 2, n);
    sort(right.begin(), right.end());
    long long best = 0;  // the empty choice
    for (long long x : left) {
        if (x > T) continue;
        auto it = upper_bound(right.begin(), right.end(), T - x);
        best = max(best, x + *prev(it));  // right contains 0 <= T - x, so it != right.begin()
    }
    return best;
}
// snippet:end

int main() {
    int n;
    long long T;
    cin >> n >> T;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << bestSubsetSum(a, T) << "\n";
}
