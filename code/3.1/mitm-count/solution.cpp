/*
Problem: count the subsets (including the empty one) of n numbers whose sum is at most T.
Input: n T (1 <= n <= 40, 0 <= T <= 10^18), then n integers (1 <= a_i <= 10^9).
Output: the number of such subsets.
*/
#include <bits/stdc++.h>
using namespace std;

// all subset sums of v[from..to-1], built one element at a time (sums reach 4 * 10^10: long long)
vector<long long> subsetSums(const vector<long long>& v, int from, int to) {
    vector<long long> sums = {0};
    for (int i = from; i < to; i++) {
        int size = sums.size();
        for (int j = 0; j < size; j++) sums.push_back(sums[j] + v[i]);  // each old subset, with v[i] added
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
    long long count = 0;  // up to 2^40 subsets
    for (long long x : left) {
        if (x > T) continue;
        // right sums y with x + y <= T are those before the first y > T - x (Theorem 3.1.4)
        count += upper_bound(right.begin(), right.end(), T - x) - right.begin();
    }
    cout << count << "\n";
}
