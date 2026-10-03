/*
Problem: CSES 1623 Apple Division. Split n apples into two groups with the smallest difference of
total weights.
Input: n (1 <= n <= 20), then p_1 .. p_n (1 <= p_i <= 10^9).
Output: the smallest difference.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> p(n);
    long long total = 0;
    for (auto& x : p) {
        cin >> x;
        total += x;
    }
    long long best = LLONG_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {  // mask = the apples in group 1
        long long s = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) s += p[i];
        best = min(best, llabs(total - 2 * s));  // group 2 weighs total - s
    }
    cout << best << "\n";
}
