#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.1.4. Meet in the middle: the subsets with sum exactly T. List the subset sums of each half, sort one list, and
// for each left sum x count the right sums equal to T - x (a block of the sorted list).
vector<long long> subsetSums(const vector<long long>& v, int from, int to) {
    vector<long long> sums = {0};
    for (int i = from; i < to; i++) {
        int size = sums.size();
        for (int j = 0; j < size; j++) sums.push_back(sums[j] + v[i]);
    }
    return sums;
}
long long countSubsetsWithSum(const vector<long long>& a, long long T) {
    int n = a.size();
    vector<long long> left = subsetSums(a, 0, n / 2), right = subsetSums(a, n / 2, n);
    sort(right.begin(), right.end());
    long long count = 0;
    for (long long x : left)
        count += upper_bound(right.begin(), right.end(), T - x) - lower_bound(right.begin(), right.end(), T - x);
    return count;
}
// snippet:end

int main() {
    cout << "subsets of 3 5 2 6 with sum 8: " << countSubsetsWithSum({3, 5, 2, 6}, 8) << '\n';
    mt19937 rng(4);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 12;
        vector<long long> a(n);
        for (auto& x : a) x = 1 + rng() % 9;
        long long T = rng() % 40, brute = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            long long s = 0;
            for (int i = 0; i < n; i++) if (mask >> i & 1) s += a[i];
            brute += s == T;
        }
        if (brute != countSubsetsWithSum(a, T)) return 1;
    }
}
