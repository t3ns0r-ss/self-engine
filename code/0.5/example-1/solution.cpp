/*
Problem: CSES 1623 Apple Division. Split n apples into two groups with the smallest difference of
total weights.
Input: n (1 <= n <= 20), then p_1 .. p_n (1 <= p_i <= 10^9).
Output: the smallest difference.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The smallest difference between the weights of two groups: one bitmask per way to split the apples.
long long smallestDifference(const vector<long long>& p) {
    int n = p.size();
    long long total = 0, best = LLONG_MAX;
    for (long long x : p) total += x;
    for (int mask = 0; mask < (1 << n); mask++) {  // mask = the apples in group 1
        long long s = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) s += p[i];
        best = min(best, llabs(total - 2 * s));  // group 2 weighs total - s
    }
    return best;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> p(n);
    for (auto& x : p) cin >> x;
    cout << smallestDifference(p) << "\n";
}
