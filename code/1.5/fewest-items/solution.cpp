/*
Problem: n items with values v_i; print the fewest items whose values add up to at least T, or -1.
Input: n T (1 <= n <= 2*10^5, 1 <= T <= 10^18), then v_1 .. v_n (1 <= v_i <= 10^9).
Output: the fewest number of items, or -1.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.5.3, part 1. The fewest items whose sum reaches T: take the largest first (-1 if even all of them fall short).
int fewestItems(vector<long long> v, long long T) {
    sort(v.rbegin(), v.rend());
    long long sum = 0;  // up to 2*10^14
    for (int k = 0; k < (int)v.size(); k++) {
        sum += v[k];
        if (sum >= T) return k + 1;
    }
    return -1;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long T;
    cin >> n >> T;
    vector<long long> v(n);
    for (auto& x : v) cin >> x;
    cout << fewestItems(v, T) << "\n";
}
