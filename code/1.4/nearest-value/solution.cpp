/*
Problem: n integers and q queries x; for each, print the integer closest to x (the smaller one if
two are equally close).
Input: n q (1 <= n, q <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9), then q values x (|x| <= 10^9).
Output: one value per line.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.4.2. For each query the value of a closest to x (the smaller one on a tie).
long long nearestValue(const vector<long long>& a, long long x) {  // a is sorted
    int n = a.size();
    int i = lower_bound(a.begin(), a.end(), x) - a.begin();  // first index with a[i] >= x
    if (i == n) return a[n - 1];  // every value is below x
    if (i == 0) return a[0];      // every value is at least x
    return (x - a[i - 1] <= a[i] - x) ? a[i - 1] : a[i];
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    sort(a.begin(), a.end());
    while (q--) {
        long long x;
        cin >> x;
        cout << nearestValue(a, x) << "\n";
    }
}
