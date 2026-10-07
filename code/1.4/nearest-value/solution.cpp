/*
Problem: n integers and q queries x; for each, print the integer closest to x (the smaller one if
two are equally close).
Input: n q (1 <= n, q <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9), then q values x (|x| <= 10^9).
Output: one value per line.
*/
#include <bits/stdc++.h>
using namespace std;

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
        // first index with a[i] >= x (Theorem 1.4.2): the closest value is there or just before
        int i = lower_bound(a.begin(), a.end(), x) - a.begin();
        long long best;
        if (i == n) best = a[n - 1];        // every value is below x
        else if (i == 0) best = a[0];       // every value is at least x
        else best = (x - a[i - 1] <= a[i] - x) ? a[i - 1] : a[i];  // ties go to the smaller
        cout << best << "\n";
    }
}
