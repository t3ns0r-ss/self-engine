#include <bits/stdc++.h>
using namespace std;

vector<long long> subsetSums(const vector<long long>& v, int from, int to) {
    vector<long long> sums = {0};
    for (int i = from; i < to; i++) {
        int size = sums.size();
        for (int j = 0; j < size; j++) sums.push_back(sums[j] + v[i]);
    }
    return sums;
}

// snippet:begin
// Theorem 3.9.3. With both lists sorted ascending, the number of right sums y <= T - x can only shrink as x grows,
// so one pointer j that only moves left finds it for every x: O(2^(n/2)) after the sorts.
long long countAtMostTwoPointers(const vector<long long>& a, long long T) {
    int n = a.size();
    vector<long long> left = subsetSums(a, 0, n / 2), right = subsetSums(a, n / 2, n);
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    long long count = 0;
    int j = right.size();  // right[0 .. j-1] are the sums that are <= T - x for the current x
    for (long long x : left) {
        while (j > 0 && right[j - 1] > T - x) j--;
        count += j;
    }
    return count;
}
// snippet:end

int main() {
    cout << "subsets of 3 5 2 6 with sum at most 7: " << countAtMostTwoPointers({3, 5, 2, 6}, 7) << '\n';
    mt19937 rng(9);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 12;
        vector<long long> a(n);
        for (auto& x : a) x = 1 + rng() % 9;
        long long T = rng() % 50, brute = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            long long s = 0;
            for (int i = 0; i < n; i++) if (mask >> i & 1) s += a[i];
            brute += s <= T;
        }
        if (brute != countAtMostTwoPointers(a, T)) return 1;
    }
}
