/*
Problem: n integers and q queries "L R"; for each, print how many of the integers lie in [L, R].
Input: n q (1 <= n, q <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9), then q lines "L R" (L <= R).
Output: one count per line.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.4.2. In a sorted array: the first index with a[i] >= x (the lower bound), and the number of elements in [L, R].
int firstAtLeast(const vector<long long>& a, long long x) {
    int lo = -1, hi = a.size();  // invariant: lo is -1 or a[lo] < x; hi is n or a[hi] >= x
    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;  // strictly between lo and hi
        if (a[mid] >= x) hi = mid;
        else lo = mid;
    }
    return hi;
}

int countInRange(const vector<long long>& a, long long L, long long R) {
    return firstAtLeast(a, R + 1) - firstAtLeast(a, L);  // elements <= R minus elements < L
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());  // the predicate a[i] >= x is monotone only on a sorted array
    while (q--) {
        long long L, R;
        cin >> L >> R;
        cout << countInRange(a, L, R) << "\n";
    }
}
