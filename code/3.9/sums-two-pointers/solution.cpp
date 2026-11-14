/*
Problem: count the subsets (including the empty one) of n numbers whose sum is at most T.
Input: n T (1 <= n <= 40, 0 <= T <= 10^18), then n integers (1 <= a_i <= 10^9).
Output: the number of such subsets.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.9.2. All subset sums of v[from..to-1]: each number is added to every sum already listed (2^k - 1 additions).
vector<long long> subsetSums(const vector<long long>& v, int from, int to) {
    vector<long long> sums = {0};
    for (int i = from; i < to; i++) {
        int size = sums.size();
        for (int j = 0; j < size; j++) sums.push_back(sums[j] + v[i]);
    }
    return sums;
}
// Theorem 3.9.3. Both lists sorted; as x grows the usable right sums shrink, so the pointer j only moves left.
long long countAtMost(const vector<long long>& a, long long T) {
    int n = a.size();
    vector<long long> left = subsetSums(a, 0, n / 2), right = subsetSums(a, n / 2, n);
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    long long count = 0;
    int j = right.size();
    for (long long x : left) {
        while (j > 0 && right[j - 1] > T - x) j--;  // T - x can be negative: j then reaches 0 and stays there
        count += j;
    }
    return count;
}
// snippet:end

int main() {
    int n;
    long long T;
    cin >> n >> T;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << countAtMost(a, T) << "\n";
}
